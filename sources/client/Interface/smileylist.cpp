#include <iostream>
#include "smileylist.h"
#include "ui_smileylist.h"

SmileyList::SmileyList(QWidget *parent, QLineEdit *edit, std::map<std::string, std::string> smileys, std::map<std::string, std::string> smileyepitech) :
    QDialog(parent),
    ui(new Ui::SmileyList),
    line(edit)
{
    QListWidget *list = new QListWidget;
    list->setViewMode(QListWidget::IconMode);
    list->setDragEnabled(false);
    QListWidget *list2 = new QListWidget;
    list2->setViewMode(QListWidget::IconMode);
    list2->setDragEnabled(false);
    ui->setupUi(this);
    ui->categories->removeTab(0);
    ui->categories->removeTab(0);
    ui->categories->addTab(list, QIcon("sources/client/ico/emote/happy.png"), "Standard");
    ui->categories->addTab(list2, QIcon("sources/client/ico/emote/epitech/steven.png"), "Epitech");
    std::string path;
    for (std::map<std::string, std::string>::iterator it = smileys.begin(); it != smileys.end(); ++it)
      {
        path = it->second.substr(10, it->second.length() - 12);
        QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(path)), "");
        item->setToolTip(QString::fromStdString(it->first));
        dynamic_cast<QListWidget *>(ui->categories->widget(0))->addItem(item);
       }
    for (std::map<std::string, std::string>::iterator it = smileyepitech.begin(); it != smileyepitech.end(); ++it)
      {
        path = it->second.substr(10, it->second.length() - 12);
        QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(path)), "");
        item->setToolTip(QString::fromStdString(it->first));
        dynamic_cast<QListWidget *>(ui->categories->widget(1))->addItem(item);
       }
    connect(ui->categories->widget(0), SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClickedSmiley(QListWidgetItem*)));
    connect(ui->categories->widget(1), SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClickedSmiley(QListWidgetItem*)));
}

void SmileyList::itemClickedSmiley(QListWidgetItem* item)
{
    line->setText(line->text() + item->toolTip());
}

SmileyList::~SmileyList()
{
    delete ui;
}


