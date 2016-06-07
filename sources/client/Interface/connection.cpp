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
        {
            QMessageBox::warning(this, tr("Error"), "Can't establish connecton with " + ui->address->text());
            return;
        }
        tmp = client;
        while (tmp->root == 0)
          tmp = tmp->next;
        tmp = tmp->next->next;
        if (ui->address->text().toStdString() == "localhost")
            ui->address->setText("127.0.0.1");
        while (tmp->root == 0)
        {
            if (tmp->fd_type != FD_FREE && std::string(tmp->ip) == ui->address->text().toStdString() && tmp->name == NULL)
              {
                tmp->name = (char *)(ui->name->text().toStdString().c_str());
                break;
              }
            tmp = tmp->next;
         }
        client_nick(tmp, (char *)ui->nick->text().toStdString().c_str(), NULL);
	client_list(tmp, NULL, NULL);
        parent_ui->chat->addTab(textEdit, QIcon("sources/client/ico/server.png"), ui->name->text());
        QTreeWidgetItem *server = addTreeRoot(parent_ui->channels, ui->name->text(), ui->address->text());
        client_list(tmp, NULL, NULL);
        // LIST + addTreeChild de tous les channels
        QTreeWidgetItem *channel = addTreeChild(server, "TEST CHANNEL" + ui->name->text(), Qt::white, "sources/client/ico/channel.png");
        // NAMES de tous les channels + addTreeChild
        addTreeChild(channel, "TEST CLIENT" + ui->nick->text(), Qt::white, "sources/client/ico/available.png");
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
