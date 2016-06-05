#ifndef SMILEYLIST_H
#define SMILEYLIST_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidgetItem>
#include <map>
#include <string>

namespace Ui {
class SmileyList;
}

class SmileyList : public QDialog
{
    Q_OBJECT

public:
    explicit SmileyList(QWidget *parent, QLineEdit *edit, std::map<std::string, std::string> smileys);
    ~SmileyList();

private slots:
    void on_list_itemClicked(QListWidgetItem *item);

private:
    Ui::SmileyList *ui;
    QLineEdit *line;
};

#endif // SMILEYLIST_H
