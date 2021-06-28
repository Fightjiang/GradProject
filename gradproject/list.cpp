#include "list.h"
#include "ui_list.h"
#include "Common.h"

List::List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::List)
{
    ui->setupUi(this);
}

List::~List()
{
    delete ui;
}

void createList(std::vector<std::string> data , bool header = true) {
    std::ofstream outfile ;
    outfile.open(SaveDotPathConst.toStdString() + "List.dot")  ;

    outfile << "digraph List {\n" ;
    outfile << "\t rankdir = LR\n" ;
    outfile << "\t Tag[label = \"L\" ,shape=none,width=0, height=0,margin=0]\n" ;
    outfile << "\t node [shape = record,tailclip = false]\n" ;
    if(header)
        outfile << "\t label0" <<"[label = \"{ <data> | <ref>  }\",style=filled]\n" ;

    for(size_t i = 1 ; i <= data.size() - 1; ++i) {
        outfile << "\t label"<< i <<"[label = \"{ <data> "<< data[i-1] <<"| <ref>  }\"]\n" ;
    }
    outfile <<"\t label"<<data.size() <<"[label = \"{ <data> " << *(data.end()-1) <<" | ^ }\"]\n" ;
    int start = 1 ;
    if(header) start = 0 ;
    outfile <<"\t Tag->label" <<start <<":data\n" ;
    for(size_t i = start ; i < data.size() ; ++i) {
        outfile<<"\t label"<< i <<":ref:c -> label"<< i + 1 <<":data [tailclip=false]\n" ;
    }
    outfile<<("}\n");
    outfile.close() ;
}


void List::on_ListSubmit_clicked()
{
    bool header = ui->header->isChecked() ;
    std::string str = ui->ListLine->text().toStdString() ;
    std::stringstream str_stream ; str_stream.str(str) ;
    std::vector<std::string> data ;
    while(str_stream.rdbuf()->in_avail()) {
        std::string tmp ; str_stream >> tmp;
        if(tmp.size() != 0) data.push_back(tmp) ;
    }
    if(data.size() == 0) {
        QMessageBox::warning(this, tr("Waring"), tr("请输入数据"), QMessageBox::Yes); return ;
    }
    createList(data , header) ;
    Save_File("List" , "List") ;
    Open_Picture("List") ;
}
