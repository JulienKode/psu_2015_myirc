#include "interface.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    t_client              *client;
    fd_set                fd_read;
    fd_set                fd_write;

    client = init_list_client();
    create_client(client, -2);
    QApplication a(argc, argv);
    Interface w(client, &fd_read, &fd_write);
    w.show();
    return a.exec();
}
