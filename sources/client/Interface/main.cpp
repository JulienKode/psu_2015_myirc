#include "interface.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    t_client client;
    QApplication a(argc, argv);
    Interface w(&client);
    w.show();
    return a.exec();
}
