#include "connection.h"

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

void Connection::on_connect_clicked()
{
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    if (ui->name->text().isEmpty() || ui->nick->text().isEmpty() || ui->address->text().isEmpty() || ui->port->text().isEmpty())
        QMessageBox::warning(this, tr("Error"), "Some parameters are empty.");
    else
    {
        //client_server(client, (char*) ui->address->text().toStdString().c_str(), (char *)ui->port->text().toStdString().c_str());
        //client_nick(client,  (char *)ui->nick->text().toStdString().c_str(), NULL);
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
