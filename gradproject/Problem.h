#ifndef PROBLEM_H
#define PROBLEM_H
#include "CreateTree.h"

std::vector<std::string> createTreeNodes(int nodes) {
    std::vector<std::string> data ;
    int Number_or_letter = QRandomGenerator::global()->bounded(3); // 0 数字; 1 小写字母 ; 2 大写字母
    for(int i = 0; i < nodes ; i++ ) {
        if(Number_or_letter == 0) {
            int tmp = 10 + QRandomGenerator::global()->bounded(190);
            data.push_back(std::to_string(tmp)) ;
        }else if(Number_or_letter == 1) {
            std::string tmp ; tmp = 'a' + QRandomGenerator::global()->bounded(26);
            data.push_back(tmp) ;
        }else {
            std::string tmp ; tmp = 'A' + QRandomGenerator::global()->bounded(26);
            data.push_back(tmp) ;
        }
    }
    return data ;
}

void preOrder(std::string &ans , TreeNode* root) {
   if(root != nullptr) {
      ans = ans + root->value + " ";
      preOrder(ans , root->lchild) ;
      preOrder(ans , root->rchild) ;
   }
}


void inOrder(std::string &ans , TreeNode* root) {
   if(root != nullptr) {
      inOrder(ans , root->lchild) ;
      ans = ans + root->value + " ";
      inOrder(ans , root->rchild) ;
   }
}

void postOrder(std::string &ans , TreeNode* root) {
   if(root != nullptr) {
      postOrder(ans , root->lchild) ;
      postOrder(ans , root->rchild) ;
      ans = ans + root->value + " ";
   }
}

int getDeep(TreeNode *root) {
    if(root == nullptr) return 0 ;
    int left = getDeep(root->lchild) ;
    int right = getDeep(root->rchild) ;
    return std::max(left , right) + 1 ;
}

int getLeafNodes(TreeNode * root) {
   if(root == nullptr) return 0 ;
   if(root->lchild == nullptr && root->rchild == nullptr) return 1 ;
   return getLeafNodes(root->lchild) + getLeafNodes(root->rchild) ;
}

int getWPL(TreeNode *root , int depth , std::string &str) {
    int sum = 0 ;
    if(root->lchild) sum = sum + getWPL(root->lchild , depth + 1 ,str ) ;
    if(root->rchild) sum = sum + getWPL(root->rchild , depth + 1 , str) ;
    if(root->lchild == nullptr && root->rchild == nullptr) {
        sum = root->num * depth ;
        str = str + std::to_string(root->num) + "*" + std::to_string(depth) + "+";
    }
    return sum ;
}

void Save_Problem(QString ProblemType, QString PngName , TreeNode* root , int NodeNumbers) {
    std::ofstream ProblemFile ;
    std::ofstream AnswerFile ;
    std::string Sequence ;


    if(ProblemType == "树的遍历") {
        createGraphvizDot(root) ;
        PngName = "Sequence" + PngName;
        Save_File("Tree", PngName) ;

        ProblemFile.open( SaveProblemPath.toStdString() + PngName.toStdString() + ".html" ) ;
        AnswerFile.open(SaveAnswerPath.toStdString() + PngName.toStdString() + ".html" ) ;

        ProblemFile << "<img src=\"../Picture/" + PngName.toStdString() ;
        ProblemFile << ".png\" height= \"400\" width=\"400\" style=\"clear: both;display:block;margin:auto;\"/>\n" ;
        ProblemFile << "<h3 style=\"text-align:center;\">请写出该二叉树的先、中、后序遍历序列。</h3>" ;

        AnswerFile << "<img src=\"../Picture/" + PngName.toStdString() ;
        AnswerFile << ".png\" height= \"400\" width=\"400\" style=\"clear: both;display:block;margin:auto;\"/>\n" ;
        Sequence = "" ; preOrder(Sequence , root) ;
        AnswerFile << "<h3 style=\"text-align:center;\">" << "先序遍历为：" << Sequence << "</h3>\n" ;
        Sequence = "" ; inOrder(Sequence , root) ;
        AnswerFile << "<h3 style=\"text-align:center;\">" << "中序遍历为：" << Sequence << "</h3>\n" ;
        Sequence = "" ; postOrder(Sequence , root) ;
        AnswerFile << "<h3 style=\"text-align:center;\">" << "后序遍历为：" << Sequence << "</h3>\n" ;

    }else if(ProblemType == "树的构造") {
        createGraphvizDot(root) ;
        PngName = "Build"  + PngName ;
        Save_File("Tree", PngName) ;

        ProblemFile.open(SaveProblemPath.toStdString() + PngName.toStdString() + ".html" ) ;
        AnswerFile.open(SaveAnswerPath.toStdString() + PngName.toStdString() + ".html" ) ;

        int NumberRand = QRandomGenerator::global()->bounded(2) + 1 ;

        std::string ProblemDescrip = "" ;
        if(NumberRand == 1) {// 先 中 构造
            Sequence = "" ; preOrder(Sequence , root) ;
            ProblemFile << "<h3 style=\"text-align:center;\">设一棵二叉树的先序序列为：" << Sequence ;
            ProblemDescrip = ProblemDescrip + "<h3 style=\"text-align:center;\">设一棵二叉树的先序序列为：" + Sequence ;
            Sequence = "" ; inOrder(Sequence , root) ;
            ProblemFile << "，中序序列：" << Sequence << "，请画出这颗树。";
            ProblemDescrip = ProblemDescrip + "，中序序列：" + Sequence + "，请画出这颗树。";
        }else { // 中 后 构造
            Sequence = "" ; inOrder(Sequence , root) ;
            ProblemFile << "<h3 style=\"text-align:center;\">设一棵二叉树的中序序列为：" << Sequence ;
            ProblemDescrip = "<h3 style=\"text-align:center;\">设一棵二叉树的中序序列为：" + Sequence ;
            Sequence = "" ; postOrder(Sequence , root) ;
            ProblemFile << "，后序序列：" << Sequence << "，请画出这颗树。";
            ProblemDescrip = ProblemDescrip + "，后序序列：" + Sequence + "，请画出这颗树。";
        }
        ProblemFile << "</h3>" ;
        AnswerFile << ProblemDescrip <<"</br>" ;

        AnswerFile << "<img src=\"../Picture/" + PngName.toStdString() ;
        AnswerFile << ".png\" height= \"400\" width=\"400\" style=\"clear: both;display:block;margin:auto;\"/>\n" ;
        Sequence = "" ; preOrder(Sequence , root) ;
        AnswerFile << "<h3 style=\"text-align:center;\">" << "先序遍历为：" << Sequence << "</h3>\n" ;
        Sequence = "" ; inOrder(Sequence , root) ;
        AnswerFile << "<h3 style=\"text-align:center;\">" << "中序遍历为：" << Sequence << "</h3>\n" ;
        Sequence = "" ; postOrder(Sequence , root) ;
        AnswerFile << "<h3 style=\"text-align:center;\">" << "后序遍历为：" << Sequence << "</h3>\n" ;

    }else if(ProblemType == "哈弗曼树"){

        std::vector<int> dataVec ;
        std::string dataStr = "" ; int dataTotal = NodeNumbers ;
        for(int i = 0 ; i < dataTotal ; ++i) {
            int tmp = QRandomGenerator::global()->bounded(30) + 5 ;
            dataVec.push_back(tmp) ;
            dataStr = dataStr + std::to_string (tmp) ;
            if(i != dataTotal - 1) dataStr = dataStr + ',' ;
        }
        PngName = "Huf"  + PngName ;
        root = createHufTree(dataVec) ;
        createGraphvizDot(root) ;
        Save_File("Tree", PngName) ;

        ProblemFile.open(SaveProblemPath.toStdString() + PngName.toStdString() + ".html" ) ;
        AnswerFile.open(SaveAnswerPath.toStdString() + PngName.toStdString() + ".html" ) ;
        std::string ProblemDescrip = "" ;
        ProblemFile << "<h3 style=\"text-align:center;\">请根据给定的权值{" ;
        ProblemFile << dataStr ;
        ProblemFile << "}，构造相应的哈夫曼树，并求出该树的带权路径长度。</h3>" ;
        ProblemDescrip = "<h3 style=\"text-align:center;\">请根据给定的权值{"  + dataStr + "}，构造相应的哈夫曼树，并求出该树的带权路径长度。</h3>" ;

        AnswerFile << ProblemDescrip <<"</br>" ;
        AnswerFile << "<img src=\"../Picture/" + PngName.toStdString() ;
        AnswerFile << ".png\" height= \"400\" width=\"400\" style=\"clear: both;display:block;margin:auto;\"/>\n" ;
        std::string WPL ;  int WplValue = getWPL(root , 0 , WPL) ;
        WPL.back() = '=' ;
        AnswerFile << "<h3 style=\"text-align:center;\">该树的带权路径长度为： " << WPL << " " <<WplValue<< "</h3>" ;
    }
    ProblemFile.close() ;
    AnswerFile.close() ;
    if(PngName.back() == '1') {
        QDesktopServices::openUrl(QUrl("file:///" +SaveAnswerPath + PngName + ".html" )) ;
        QDesktopServices::openUrl(QUrl("file:///" +SaveProblemPath + PngName + ".html" )) ;
    }
}


#endif // PROBLEM_H
