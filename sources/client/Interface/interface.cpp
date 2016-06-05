#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "interface.h"
#include "connection.h"
#include "smileylist.h"
#include "../../../includes/irc.h"

Interface::Interface(t_client *client, fd_set *fd_read, fd_set *fd_write, QWidget *parent) :
    QDialog(parent),
    fd_read(fd_read),
    fd_write(fd_write),
    client(client),
    ui(new Ui::Interface)
{
     DIR *pdir;
     struct dirent *pent;

     _select = false;
     pdir=opendir("../ico/emote");
     if (!pdir){
     printf ("Smileys loading failure ...");
     exit(1);
     }

     std::string name;
     while ((pent = readdir(pdir)))
     {
        name = pent->d_name;
        if (name.length() > 4 && name[name.length() - 4] == '.')
             smileys["[" + name.substr(0, name.length() - 4) + "]"] = "<img src='../ico/emote/" + name +"'>";
     }
     closedir(pdir);
     pdir=opendir("../ico/emote/epitech");
     if (!pdir){
     printf ("Smileys loading failure ...");
     exit(1);
     }

     while ((pent = readdir(pdir)))
     {
        name = pent->d_name;
        if (name.length() > 4 && name[name.length() - 4] == '.')
             smileyepitech["[" + name.substr(0, name.length() - 4) + "]"] = "<img src='../ico/emote/epitech/" + name +"'>";
     }
     closedir(pdir);
     ui_setup = false;
     ui->setupUi(this);
     ui_setup = true;
     ui->chat->setTabsClosable(true);
     ui->chat->removeTab(0);
     ui->chat->removeTab(0);
     ui->smileys->setIcon(QIcon("../ico/emote/happy.png"));
     QTimer *timer = new QTimer();
     timer->connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
     timer->start(100);
}

void Interface::refresh()
{
    struct timeval t;
    t_client *tmp;
    char *buf;
    t.tv_sec = 0;
    t.tv_usec = 40;

    if (ui_setup)
    {
        init_fd_set_client(client, fd_read, fd_write);
        if (_select)
        {
            if (select(MAX_FD + 1, fd_read, fd_write, NULL, &t) == -1)
             exit(42);
        }
        tmp = client->next->next;
        while (tmp->root == 0)
        {
              if (tmp->fd_type != FD_FREE && tmp->circbuff_r == 1)
              {
                  buf = get_buff_read_underground(tmp);
                  // Avant d'AddText, faire du parsing pour savoir si c'est le retour d'une commande, un message privé ou autre
                  if (buf)
                    addText(tmp->name, buf);
              }
           tmp = tmp->next;
        }
    fd_action_client(client, fd_read, fd_write);
    }
}

Interface::~Interface()
{
    delete ui;
}

int list_counts(t_client *client)
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

void Interface::on_connect_clicked()
{
    Connection w(client, this, ui);

    int i = list_counts(client);
    w.show();
    w.exec();
    if (i != list_counts(client))
        _select = true;
}

void Interface::on_smileys_clicked()
{
    SmileyList w(this, ui->message, smileys, smileyepitech);
    w.show();
    w.exec();
}

std::string Interface::format_message(char *m)
{
  std::string msg(m);

  size_t index = 0;
  while (42)
  {
       index = msg.find(ui->label->text().toStdString(), index);
       if (index == std::string::npos)
           break;
       msg.replace(index, ui->label->text().length(), "<font color=\"red\">" + ui->label->text().toStdString() + "</font>");
       index += ui->label->text().length() + std::string("<font color=\"red\">").length() + std::string("</font>").length();
  }
  for (std::map<std::string, std::string>::iterator it = smileys.begin(); it != smileys.end(); ++it)
    {
      size_t index = 0;
      while (42)
      {
           index = msg.find(it->first, index);
           if (index == std::string::npos)
               break;
           msg.replace(index, it->first.length(), it->second);
           index += it->second.length();
      }
    }
  for (std::map<std::string, std::string>::iterator it = smileyepitech.begin(); it != smileyepitech.end(); ++it)
    {
      size_t index = 0;
      while (42)
      {
           index = msg.find(it->first, index);
           if (index == std::string::npos)
               break;
           msg.replace(index, it->first.length(), it->second);
           index += it->second.length();
      }
    }
  return (msg);
}

void Interface::on_message_returnPressed()
{
    on_send_clicked();
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

void Interface::addText(char *tab, char *msg)
{
   int i;
   for (i = 0; i < ui->chat->count(); i++)
   {
        if (ui->chat->tabText(i) == QString(tab)) // A Tester : Que si les deux sont sur le même serveur.
            break;
   }
   QTextEdit *textEditor = dynamic_cast<QTextEdit *>(ui->chat->widget(i - 1));
   textEditor->moveCursor (QTextCursor::End);
   textEditor->textCursor().insertHtml(QString(format_message(msg).c_str()) + "<br>");
   textEditor->moveCursor (QTextCursor::End);
}

void Interface::on_channels_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    if (item->parent())
    {
        if (item->text(column).toStdString()[0] == '#' || item->text(column).toStdString()[0] == '&')
        {
           for (int i = 0; i < ui->chat->count(); i++)
              {
                if (ui->chat->tabText(i) == item->text(column)) // A Tester : Que si les deux sont sur le même serveur.
                    return;
               }
          // JOIN (char *)item->text().toStdString().c_str() sur la socket du serveur item->parent->text().toStdString().c_str()
          // Si JOIN reussit
        //   {
                ui->chat->addTab(textEdit, QIcon("../ico/channel.png"), item->text(column));
               //faire un USERS pour remplir la liste des utilisateurs connectés
            //}
        }
        else
        {
            // Si c'est un client :
            for(int i = 0; i < ui->chat->count(); i++)
               {
                 if (ui->chat->tabText(i) == item->text(column)) // A Tester : Que si les deux sont sur le même serveur.
                     return;
               }
             ui->chat->addTab(textEdit, QIcon("../ico/chat.png"), item->text(column));
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

void Interface::on_send_clicked()
{
    if (!ui->message->text().isEmpty())
    {
        // Si c'est une commande, executer la commande sur le serveur actif
        // Sinon PRIVMSG ui->chat->tabText(ui->chat->currentIndex()) ui->message->text sur le serveur actif
    }
    ui->message->setText("");
}

// Refresh en masse la liste ui->channels et le chat
// Si on reçoit un PRIVMSG, ouvrir une tab (si elle n'est pas deja ouverte), sinon écrite dans la tab ouverte et surligner nom en rouge
// A chaque envoi depuis le client, décaler la structure client avant d'appeler la fonction (ex : nick)

