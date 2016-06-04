#include <iostream>
#include "interface.h"
#include "connection.h"

Interface::Interface(t_client *client, QWidget *parent) :
    QDialog(parent),
    client(client),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    ui->chat->setTabsClosable(true);
    ui->chat->removeTab(0);
    ui->chat->removeTab(0);
}

Interface::~Interface()
{
    delete ui;
}
void Interface::on_send_clicked()
{
    if (!ui->message->text().isEmpty())
    {
        // Si c'est une commande, executer la commande
        // Sinon PRIVMSG ui->chat->tabText(ui->chat->currentIndex()) ui->message->text sur le serveur concerné
    }
}

QTreeWidgetItem *addTreeRoot(QTreeWidget *tree, QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(tree);
    treeItem->setIcon(0, QIcon("../ico/server.png"));
    treeItem->setText(0, name);
    treeItem->setToolTip(0, description);
    return treeItem;
}

QTreeWidgetItem *addTreeChild(QTreeWidgetItem *parent, QString name, Qt::GlobalColor color, QString ico)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setBackground(0, color);
    treeItem->setIcon(0, QIcon(ico));
    parent->addChild(treeItem);
    return treeItem;
}

void Interface::on_connect_clicked()
{
    Connection w(client, this, ui);
    w.show();
    w.exec();
}

void Interface::on_channels_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent())
    {
        if (item->text(column).toStdString()[0] == '#' || item->text(column).toStdString()[0] == '&')
        {
           for (int i = 0; i < ui->chat->count(); i++)
              {
                if (ui->chat->tabText(i) == item->text(column)) // Tester que si sur le même serveur
                    return;
               }
          // JOIN (char *)item->text().toStdString().c_str() sur la socket du serveur item->parent->text().toStdString().c_str()
          // Si JOIN reussit
        //   {
                ui->chat->addTab(new QListWidget, QIcon("../ico/channel.png"), item->text(column));
               //faire un USERS pour remplir la liste des utilisateurs connectés
            //}
        }
        else
        {
            // Si c'est un client :
            for(int i = 0; i < ui->chat->count(); i++)
               {
                 if (ui->chat->tabText(i) == item->text(column)) // Tester que si sur le même serveur
                     return;
               }
             ui->chat->addTab(new QListWidget, QIcon("../ico/chat.png"), item->text(column));
        }
    }
}

void Interface::on_chat_tabCloseRequested(int index)
{
    QString name = ui->chat->tabText(ui->chat->currentIndex());
    // Si name est un serveur, QUIT le serveur. Dans ce cas, fermer toutes les tabs relatives à ce serveur (channels + utilisateurs)
    // Si name est un channel, PART le channel
    ui->chat->removeTab(index);
}

// Refresh en masse la liste ui->channels
