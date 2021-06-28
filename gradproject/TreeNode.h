#ifndef TREENODE_H
#define TREENODE_H

#include "string"
#include "iostream"

class TreeNode {

public :
    TreeNode(int value){
        this->num = value ;
        this->lchild = nullptr ;
        this->rchild = nullptr ;
    }

    TreeNode(std::string value){
        this->value = value ;
        this->lchild = nullptr ;
        this->rchild = nullptr ;
    }

    int num ;
    std:: string value ;
    int height ;
    TreeNode *lchild ;
    TreeNode *rchild ;

};

#endif // TREENODE_H
