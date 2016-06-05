/********************************************************************************
** Form generated from reading UI file 'connection.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTION_H
#define UI_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Connection
{
public:
    QLabel *label;
    QPushButton *connect;
    QPushButton *return_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *name;
    QLineEdit *address;
    QLineEdit *port;
    QLineEdit *nick;

    void setupUi(QDialog *Connection)
    {
        if (Connection->objectName().isEmpty())
            Connection->setObjectName(QStringLiteral("Connection"));
        Connection->resize(317, 175);
        label = new QLabel(Connection);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 181, 41));
        QFont font;
        font.setFamily(QStringLiteral("Saab"));
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        connect = new QPushButton(Connection);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(160, 140, 111, 31));
        return_2 = new QPushButton(Connection);
        return_2->setObjectName(QStringLiteral("return_2"));
        return_2->setGeometry(QRect(40, 140, 111, 31));
        label_2 = new QLabel(Connection);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 181, 41));
        label_2->setFont(font);
        label_3 = new QLabel(Connection);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 181, 41));
        label_3->setFont(font);
        label_4 = new QLabel(Connection);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 100, 181, 41));
        label_4->setFont(font);
        name = new QLineEdit(Connection);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(170, 10, 141, 27));
        address = new QLineEdit(Connection);
        address->setObjectName(QStringLiteral("address"));
        address->setGeometry(QRect(170, 40, 141, 27));
        port = new QLineEdit(Connection);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(170, 70, 141, 27));
        nick = new QLineEdit(Connection);
        nick->setObjectName(QStringLiteral("nick"));
        nick->setGeometry(QRect(170, 100, 141, 27));

        retranslateUi(Connection);

        QMetaObject::connectSlotsByName(Connection);
    } // setupUi

    void retranslateUi(QDialog *Connection)
    {
        Connection->setWindowTitle(QApplication::translate("Connection", "IRC Client v1.0 - Connection", 0));
        label->setText(QApplication::translate("Connection", "Server Name", 0));
#ifndef QT_NO_TOOLTIP
        connect->setToolTip(QApplication::translate("Connection", "<html><head/><body><p>Envoyer la t\303\242che au programme</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        connect->setText(QApplication::translate("Connection", "Connect", 0));
#ifndef QT_NO_TOOLTIP
        return_2->setToolTip(QApplication::translate("Connection", "<html><head/><body><p>Envoyer la t\303\242che au programme</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        return_2->setText(QApplication::translate("Connection", "Return", 0));
        label_2->setText(QApplication::translate("Connection", "Address", 0));
        label_3->setText(QApplication::translate("Connection", "Port", 0));
        label_4->setText(QApplication::translate("Connection", "Nickname", 0));
        name->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Connection: public Ui_Connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTION_H
