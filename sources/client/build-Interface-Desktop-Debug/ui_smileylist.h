/********************************************************************************
** Form generated from reading UI file 'smileylist.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMILEYLIST_H
#define UI_SMILEYLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmileyList
{
public:
    QTabWidget *categories;
    QWidget *tab;
    QTextEdit *textEdit;
    QWidget *tab_2;
    QListWidget *list;

    void setupUi(QDialog *SmileyList)
    {
        if (SmileyList->objectName().isEmpty())
            SmileyList->setObjectName(QStringLiteral("SmileyList"));
        SmileyList->resize(246, 300);
        categories = new QTabWidget(SmileyList);
        categories->setObjectName(QStringLiteral("categories"));
        categories->setGeometry(QRect(0, 0, 241, 311));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 561, 411));
        categories->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        list = new QListWidget(tab_2);
        list->setObjectName(QStringLiteral("list"));
        list->setGeometry(QRect(0, 0, 241, 301));
        categories->addTab(tab_2, QString());

        retranslateUi(SmileyList);

        categories->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SmileyList);
    } // setupUi

    void retranslateUi(QDialog *SmileyList)
    {
        SmileyList->setWindowTitle(QApplication::translate("SmileyList", "IRC Client  v1.0 - Smileys", 0));
        categories->setTabText(categories->indexOf(tab), QApplication::translate("SmileyList", "Tab 1", 0));
        categories->setTabText(categories->indexOf(tab_2), QApplication::translate("SmileyList", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class SmileyList: public Ui_SmileyList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMILEYLIST_H
