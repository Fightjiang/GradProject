#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "list.h"
#include "tree.h"
#include "graph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_List_clicked()
{
    List *list = new List(this);
    list->show();
}

void MainWindow::on_Tree_clicked()
{
    Tree *tree = new Tree(this);
    tree->show();
}

void MainWindow::on_Graph_clicked()
{
    Graph *graph = new Graph(this);
    graph->show();
}
