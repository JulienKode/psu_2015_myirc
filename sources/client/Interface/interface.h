#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include <map>
#include "../../../includes/irc.h"
#include "ui_interface.h"

namespace Ui {
class Interface;
}

class Interface : public QDialog
{
    Q_OBJECT

public:
    explicit Interface(t_client *, fd_set *, fd_set *, QWidget *parent = 0);
    ~Interface();
    void addText(char *tab, char *msg);
    std::string format_message(char *m);
private slots:
    void on_send_clicked();

    void on_connect_clicked();

    void on_channels_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_chat_tabCloseRequested(int index);

    void on_smileys_clicked();

    void refresh();

    void on_message_returnPressed();

private:
    bool                    _select;
    bool ui_setup;
    fd_set                *fd_read;
    fd_set                *fd_write;
    std::map<std::string, std::string> smileys;
    std::map<std::string, std::string> smileyepitech;
    t_client *client;
    Ui::Interface *ui;
};

QTreeWidgetItem *addTreeRoot(QTreeWidget *, QString name, QString description);
QTreeWidgetItem *addTreeChild(QTreeWidgetItem *parent, QString name, Qt::GlobalColor, QString);

#endif // INTERFACE_H
