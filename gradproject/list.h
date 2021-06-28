#ifndef LIST_H
#define LIST_H

#include <QDialog>


namespace Ui {
class List;
}

class List : public QDialog
{
    Q_OBJECT

public:
    explicit List(QWidget *parent = nullptr);
    ~List();

private slots:
    void on_ListSubmit_clicked();

private:
    Ui::List *ui;
};



#endif // LIST_H
