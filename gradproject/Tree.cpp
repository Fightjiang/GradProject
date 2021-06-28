#include "tree.h"
#include "ui_tree.h"
#include "Problem.h"


Tree::Tree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tree)
{
    ui->setupUi(this);
    this->set_Visible_false() ;
    this->on_Push_problems_clicked() ;
}

Tree::~Tree()
{
    delete ui;
}

void Tree::set_Visible_false() {
    ui->Problem_Submit->setVisible(false) ;
    ui->BT_Submit->setVisible(false) ;
    ui->BST_Submit->setVisible(false) ;
    ui->AVL_Submit->setVisible(false) ;
    ui->Huf_Submit->setVisible(false) ;
    ui->Max_heap->setVisible(false) ;
    ui->Min_heap->setVisible(false) ;
    ui->BST_Line->setVisible(false) ;
    ui->Huf_Line->setVisible(false) ;
    ui->Heap_Line->setVisible(false) ;
    ui->BTLine->setVisible(false) ;
    ui->Node->setVisible(false) ;
    ui->Nodes->setVisible(false) ;
    ui->Problem->setVisible(false) ;
    ui->Problem_Number->setVisible(false) ;
    ui->Problem_Type->setVisible(false) ;
    ui->Problem_Types->setVisible(false) ;
    ui->Huf_Line->setText("") ;
    ui->BTLine->setText("") ;
    ui->Heap_Line->setText("") ;
    ui->Problem->setValue(0) ;
    ui->Node->setValue(0) ;
}

void Tree::on_Push_problems_clicked()
{
    this->set_Visible_false() ;
    /*
    ui->BinTree->setVisible(false) ;
    ui->BST->setVisible(false) ;
    ui->Hufman->setVisible(false) ;
    ui->Heap_Button->setVisible(false) ;
    */
    ui->Node->setVisible(true) ;
    ui->Nodes->setVisible(true) ;
    ui->Problem->setVisible(true) ;
    ui->Problem_Number->setVisible(true) ;
    ui->Problem_Submit->setVisible(true) ;
    ui->Problem_Type->setVisible(true) ;
    ui->Problem_Types->setVisible(true) ;
}

void Tree::on_BinTree_clicked()
{
    this->set_Visible_false() ;
    ui->BTLine->setVisible(true) ;
    ui->BT_Submit->setVisible(true) ;
}

void Tree::on_BST_clicked()
{
    this->set_Visible_false() ;
    ui->BST_Line->setVisible(true) ;
    ui->BST_Submit->setVisible(true) ;
    ui->AVL_Submit->setVisible(true) ;
}

void Tree::on_Hufman_clicked()
{
    this->set_Visible_false() ;
    ui->Huf_Line->setVisible(true) ;
    ui->Huf_Submit->setVisible(true) ;
}

void Tree::on_Heap_Button_clicked()
{
    this->set_Visible_false() ;
    ui->Heap_Line->setVisible(true) ;
    ui->Max_heap->setVisible(true) ;
    ui->Min_heap->setVisible(true) ;
}

void Tree::on_BT_Submit_clicked()
{
    std::string str = ui->BTLine->text().toStdString() ;
    std::stringstream str_stream ; str_stream.str(str) ;
    std::vector<std::string> data ;
    while(str_stream.rdbuf()->in_avail()) {
        std::string tmp ; str_stream >> tmp;
        if(tmp.size() != 0) data.push_back(tmp) ;
    }
    if(data.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    size_t i = 0 ;
    TreeNode *root = createBinTree(data , i);
    createGraphvizDot(root) ;
    Save_File("Tree","BinTree") ;
    DestoryTree(root) ;
    Open_Picture("BinTree") ;
    //QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);
}

void Tree::on_AVL_Submit_clicked()
{
    std::string str = ui->BST_Line->text().toStdString() ;
    std::vector<int> nums ; String_To_Numbers(nums , str) ;
    std::sort(nums.begin() , nums.end()) ;
    if(nums.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    TreeNode *root = createAVLTree(nums , 0 , nums.size() - 1) ;
    createGraphvizDot(root) ;
    Save_File("Tree","AVLTree") ;

    DestoryTree(root) ;
    Open_Picture("AVLTree") ;
    //QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);
}

void Tree::on_BST_Submit_clicked()
{
    std::string str = ui->BST_Line->text().toStdString() ;
    std::vector<int> nums ; String_To_Numbers(nums , str) ;
    if(nums.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    TreeNode *root = createBSTree(nums) ;
    createGraphvizDot(root) ;
    Save_File("Tree","BSTree") ;
    DestoryTree(root) ;
    Open_Picture("BSTree") ;
    //QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);
}

void Tree::on_Huf_Submit_clicked()
{
    std::string str = ui->Huf_Line->text().toStdString() ;
    std::vector<int> nums ; String_To_Numbers(nums , str) ;
    if(nums.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    TreeNode *root = createHufTree(nums) ;
    createGraphvizDot(root) ;
    Save_File("Tree","HufTree") ;
    DestoryTree(root) ;
    Open_Picture("HufTree") ;
    //QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);
}

void Tree::on_Max_heap_clicked()
{
    std::string str = ui->Heap_Line->text().toStdString() ;
    std::vector<int> nums ; String_To_Numbers(nums , str) ;
    if(nums.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    TreeNode *root = createMaxHeap(nums) ;
    createGraphvizDot(root) ;
    Save_File("Tree","MaxHeap") ;
    DestoryTree(root) ;
    Open_Picture("MaxHeap") ;
    //QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);
}

void Tree::on_Min_heap_clicked()
{
    std::string str = ui->Heap_Line->text().toStdString() ;
    std::vector<int> nums ; String_To_Numbers(nums , str) ;
    if(nums.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    TreeNode *root = createMinHeap(nums) ;
    createGraphvizDot(root) ;
    Save_File("Tree","MinHeap") ;
    DestoryTree(root) ;
    Open_Picture("MinHeap") ;
    //QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);
}

void Tree::on_Problem_Submit_clicked()
{
    QString ProblemType =ui->Problem_Type->currentText() ;
    int ProblemNumbers = ui->Problem->value() ;
    int NodeNumbers = ui->Node->value() ;
    if(ProblemNumbers == 0 || NodeNumbers == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    for(int i = 0 ; i < ProblemNumbers ; ++i) {
        std::vector<std::string> data = createTreeNodes(NodeNumbers) ;
        TreeNode *root = createRandomBinTree(NodeNumbers , data);
        Save_Problem(ProblemType , "BinTree" + QString::number(i+1) , root , NodeNumbers) ;
        DestoryTree(root) ;
        Sleep(400);//给 I/O 操作多点的时间，防止错误
    }
    QMessageBox::information(this, tr("Success"), tr("成功，请在当前目录下查看！"), QMessageBox::Yes);

}
/*
A # B C # # #
3 7 # 5 # # #
27 6 # # 14 4 # # 5 0 # # 3 # #
*/
