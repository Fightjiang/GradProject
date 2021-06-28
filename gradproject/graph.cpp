#include "graph.h"
#include "ui_graph.h"
#include "Common.h"

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
}

Graph::~Graph()
{
    delete ui;
}

void Graphinput(std::vector<std::vector<QString>> &Edge , QString strInput) {
    QStringList strlist = strInput.split("\n");
    for (int i = 0; i < strlist.length(); i++)
    {
        QStringList list = strlist[i].split(" ");
        std::vector<QString> tmpVec ;
        for(int j = 0 ; j < list.length() ; ++j ){
            tmpVec.push_back(list[j]) ;
        }
        Edge.push_back(tmpVec) ;
    }
}

void CreateGraphDot(std::vector<std::vector<QString>> Edge , bool DirectedFlag) {
    std::string GraphName = (DirectedFlag == true) ? "digraph" : "graph" ;
    std::string Direct = (DirectedFlag == true) ? "->" : "--" ;
    std::map<std::pair<QString,QString> , int > mp ;

    for(size_t i = 0 ; i < Edge.size() ; ++i) {
        for(size_t j = 1 ; j < Edge[i].size() ; ++j)  {
            mp[std::make_pair(Edge[i][0] , Edge[i][j])] = 1 ;
            if(mp.find(std::make_pair(Edge[i][j] , Edge[i][0])) != mp.end()) {
                mp[std::make_pair(Edge[i][0] , Edge[i][j])] = 2 ; // 双向奔赴
                mp[std::make_pair(Edge[i][j] , Edge[i][0])] = 2 ;
            }
        }
    }
    std::ofstream outfile ;
    outfile.open( SaveDotPathConst.toStdString() + "graph.dot") ;

    outfile << GraphName <<" g {\n" ;
    outfile << ("\tnode [shape=circle,fontsize=25,penwidth=3,fontname=\"Times New Roman, Bold\",margin=\"0.04,0.02\"]\n");
    outfile << ("\tedge[fontsize=25,penwidth=3,fontname=\"Times New Roman, Bold\"]\n");


    for(size_t i = 0 ; i < Edge.size() ; ++i) {
        QString head = Edge[i][0] ;
        for(size_t j = 1 ; j < Edge[i].size() ; ++j) {
            if(mp[std::make_pair(Edge[i][0] , Edge[i][j])] == 0) continue ;
            outfile << "\t" << head.toStdString() << Direct << Edge[i][j].toStdString()  ;
            if(mp[std::make_pair(Edge[i][0] , Edge[i][j])] == 2) {
                mp[std::make_pair(Edge[i][j] , Edge[i][0])] = 0 ;
                if(DirectedFlag) outfile <<"[dir=\"both\"]" ;
            }
            outfile <<"\n" ;
        }
    }

    outfile <<"}\n" ;
    outfile.close() ;

}

void Graph::on_pushButton_clicked()
{
    QString strInput = ui->Graphinput->toPlainText().trimmed();
    if(strInput.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }

    std::vector<std::vector<QString>> Edge ;
    Graphinput(Edge , strInput) ;
    bool DirectedFlag = ui->Directed->isChecked() ;
    CreateGraphDot(Edge , DirectedFlag) ;
    Save_File("graph" , "Graph") ;
    Open_Picture("Graph") ;

}
