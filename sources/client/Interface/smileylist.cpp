#include <iostream>
#include "smileylist.h"
#include "ui_smileylist.h"

SmileyList::SmileyList(QWidget *parent, QLineEdit *edit, std::map<std::string, std::string> smileys) :
    QDialog(parent),
    ui(new Ui::SmileyList),
    line(edit)
{
    ui->setupUi(this);
    ui->list->setViewMode(QListWidget::IconMode);
    ui->list->setDragEnabled(false);
    std::string path;
    for (std::map<std::string, std::string>::iterator it = smileys.begin(); it != smileys.end(); ++it)
      {
        path = it->second.substr(10, it->second.length() - 12);
        QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString(path)), "");
        item->setToolTip(QString::fromStdString(it->first));
        ui->list->addItem(item);
       }
}

SmileyList::~SmileyList()
{
    delete ui;
}

void SmileyList::on_list_itemClicked(QListWidgetItem *item)
{
    line->setText(line->text() + item->toolTip());
}
