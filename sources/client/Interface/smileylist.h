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
    explicit SmileyList(QWidget *parent, QLineEdit *edit, std::map<std::string, std::string> smileys, std::map<std::string, std::string> smileyepitech);
    ~SmileyList();

private slots:
    void itemClickedSmiley(QListWidgetItem* item);
private:
    Ui::SmileyList *ui;
    QLineEdit *line;
};

#endif // SMILEYLIST_H
