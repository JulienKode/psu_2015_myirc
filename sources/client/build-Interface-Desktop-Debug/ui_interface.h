/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QLineEdit *message;
    QLabel *label;
    QTreeWidget *channels;
    QPushButton *send;
    QPushButton *connect;
    QTabWidget *chat;
    QWidget *tab;
    QTextEdit *textEdit;
    QWidget *tab_2;
    QPushButton *smileys;

    void setupUi(QDialog *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QStringLiteral("Interface"));
        Interface->resize(763, 494);
        message = new QLineEdit(Interface);
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(120, 460, 491, 27));
        label = new QLabel(Interface);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 465, 91, 17));
        channels = new QTreeWidget(Interface);
        channels->setObjectName(QStringLiteral("channels"));
        channels->setGeometry(QRect(10, 10, 171, 411));
        send = new QPushButton(Interface);
        send->setObjectName(QStringLiteral("send"));
        send->setGeometry(QRect(670, 460, 81, 27));
        connect = new QPushButton(Interface);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(10, 425, 171, 27));
        chat = new QTabWidget(Interface);
        chat->setObjectName(QStringLiteral("chat"));
        chat->setGeometry(QRect(190, 10, 561, 441));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 561, 411));
        chat->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        chat->addTab(tab_2, QString());
        smileys = new QPushButton(Interface);
        smileys->setObjectName(QStringLiteral("smileys"));
        smileys->setGeometry(QRect(615, 460, 51, 27));

        retranslateUi(Interface);

        chat->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QDialog *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "IRC Client v1.0", 0));
        message->setText(QString());
        label->setText(QApplication::translate("Interface", "Anonymous : ", 0));
        QTreeWidgetItem *___qtreewidgetitem = channels->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Interface", "Servers", 0));
        send->setText(QApplication::translate("Interface", "Send", 0));
        connect->setText(QApplication::translate("Interface", "Connect", 0));
        chat->setTabText(chat->indexOf(tab), QApplication::translate("Interface", "Tab 1", 0));
        chat->setTabText(chat->indexOf(tab_2), QApplication::translate("Interface", "Tab 2", 0));
        smileys->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
