#pragma once

#include <QDialog>
#include <QMessageBox>
#include "../../../includes/irc.h"
#include "interface.h"
#include "ui_connection.h"

namespace Ui {
class Connection;
class Interface;
}

class Connection : public QDialog
{
    Q_OBJECT

public:
    Connection(t_client *, QWidget *, Ui::Interface *);
    ~Connection();

private slots:

    void on_connect_clicked();

    void on_return_2_clicked();

private:
    t_client *client;
    Ui::Connection *ui;
    Ui::Interface *parent_ui;
};
