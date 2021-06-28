#ifndef TREE_H
#define TREE_H

#include <QDialog>

namespace Ui {
class Tree;
}

class Tree : public QDialog
{
    Q_OBJECT

public:
    explicit Tree(QWidget *parent = nullptr);
    ~Tree();

private slots:
    void on_Push_problems_clicked();
    void set_Visible_false();

    void on_BinTree_clicked();

    void on_BST_clicked();

    void on_Hufman_clicked();

    void on_Heap_Button_clicked();

    void on_BT_Submit_clicked();

    void on_AVL_Submit_clicked();

    void on_BST_Submit_clicked();

    void on_Huf_Submit_clicked();

    void on_Max_heap_clicked();

    void on_Min_heap_clicked();

    void on_Problem_Submit_clicked();

private:
    Ui::Tree *ui;
};

#endif // TREE_H
