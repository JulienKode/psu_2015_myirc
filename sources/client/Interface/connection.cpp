#include "connection.h"
#include <iostream>

Connection::Connection(t_client *client, QWidget *parent, Ui::Interface *parent_ui) :
    QDialog(parent),
    client(client),
    ui(new Ui::Connection),
    parent_ui(parent_ui)
{
    ui->setupUi(this);
}

Connection::~Connection()
{
    delete ui;
}

int list_count(t_client *client)
{
   t_client *tmp;
   int i;

   i = 0;
   tmp = client;
   while (tmp->root == 0)
    tmp = tmp->next;
   tmp = tmp->next->next;
   while (tmp->root == 0)
   {
       if (tmp->fd_type != FD_FREE)
           i++;
    tmp = tmp->next;
   }
return (i);
}

void Connection::on_connect_clicked()
{
    t_client *tmp;
    int nb_serv = list_count(client);
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    if (ui->name->text().isEmpty() || ui->nick->text().isEmpty() || ui->address->text().isEmpty() || ui->port->text().isEmpty())
        QMessageBox::warning(this, tr("Error"), "Some parameters are empty.");
    else
    {
        client_server(client, (char*) ui->address->text().toStdString().c_str(), (char *)ui->port->text().toStdString().c_str());
        if (list_count(client) == nb_serv)
            return;
        tmp = client;
        while (tmp->root == 0)
          tmp = tmp->next;
        tmp = tmp->next->next;
        while (tmp->root == 0)
        {
            if (tmp->fd_type != FD_FREE && std::string(tmp->ip) == ui->address->text().toStdString() && tmp->name == NULL)
              {
                 std::cout << tmp->ip << " => " << tmp->name << std::endl;
                tmp->name = (char *)(ui->name->text().toStdString().c_str());
                break;
              }
            tmp = tmp->next;
         }
        if (tmp->root == 1)
            return;
//        client_nick(client, (char *)ui->nick->text().toStdString().c_str(), NULL);
        parent_ui->chat->addTab(textEdit, QIcon("../ico/server.png"), ui->name->text());
        QTreeWidgetItem *server = addTreeRoot(parent_ui->channels, ui->name->text(), ui->address->text());
        // LIST + addTreeChild de tous les channels
        QTreeWidgetItem *channel = addTreeChild(server, "TEST CHANNEL" + ui->name->text(), Qt::white, "../ico/channel.png");
        // NAMES de tous les channels + addTreeChild
        addTreeChild(channel, "TEST CLIENT" + ui->nick->text(), Qt::white, "../ico/available.png");
        parent_ui->label->setText(ui->nick->text());
        parent_ui->channels->expandAll();
        parent_ui->channels->resizeColumnToContents(0);
        this->close();
    }
}

void Connection::on_return_2_clicked()
{
    this->close();
}
