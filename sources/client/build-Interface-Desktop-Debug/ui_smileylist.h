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

QT_BEGIN_NAMESPACE

class Ui_SmileyList
{
public:
    QListWidget *list;

    void setupUi(QDialog *SmileyList)
    {
        if (SmileyList->objectName().isEmpty())
            SmileyList->setObjectName(QStringLiteral("SmileyList"));
        SmileyList->resize(400, 300);
        list = new QListWidget(SmileyList);
        list->setObjectName(QStringLiteral("list"));
        list->setGeometry(QRect(0, 0, 401, 301));

        retranslateUi(SmileyList);

        QMetaObject::connectSlotsByName(SmileyList);
    } // setupUi

    void retranslateUi(QDialog *SmileyList)
    {
        SmileyList->setWindowTitle(QApplication::translate("SmileyList", "IRC Client  v1.0 - Smileys", 0));
    } // retranslateUi

};

namespace Ui {
    class SmileyList: public Ui_SmileyList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMILEYLIST_H
