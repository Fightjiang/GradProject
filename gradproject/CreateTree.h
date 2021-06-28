#ifndef CREATETREE_H
#define CREATETREE_H
#include "TreeNode.h"
#include "Common.h"

struct cmp {
    bool operator() (const TreeNode* A , const TreeNode* B) {
        return A->num > B->num ;
    }
};

TreeNode* createBinTree(std::vector<std::string> &data , size_t& i)
{
   TreeNode *root ;
   if(i >= data.size() || "#" == data[i])
      root = nullptr;
   else {
      root = new TreeNode(data[i]);
      root->lchild = createBinTree(data , ++i);
      root->rchild = createBinTree(data , ++i);
   }
   return root ;
}

TreeNode* createAVLTree(std::vector<int> &nums , int left , int right) {
    if(left > right) return nullptr ;
    int mild = left + (right - left) / 2 ;
    TreeNode *root = new TreeNode(nums[mild]) ;
    root->lchild = createAVLTree(nums , left , mild - 1) ;
    root->rchild = createAVLTree(nums , mild + 1 , right) ;
    return root ;
}

TreeNode* createBSTree(std::vector<int> &nums) {
    TreeNode *root = new TreeNode(*nums.begin());
    for(size_t i = 1 ; i < nums.size() ; ++i) {
        TreeNode *node = new TreeNode(nums[i]) ;
        TreeNode *current = root ;
        while(true) {
            if(nums[i] < current->num) {
                if(current->lchild == nullptr) {
                    current->lchild = node ;
                    break ;
                }
                current = current->lchild ;
            }else {
                if(current->rchild == nullptr) {
                    current->rchild = node ;
                    break ;
                }
                 current = current->rchild ;
            }
        }
    }
    return root ;
}

TreeNode* createHufTree(std::vector<int> &nums ) {
    std::priority_queue<TreeNode* , std::vector<TreeNode*> , cmp > que ;
    for(auto num : nums ) {
        TreeNode* tmp = new TreeNode(num) ;
        que.push(tmp) ;
    }
    while(que.size() > 1) {
        TreeNode *tmp = new TreeNode(0) ;
        tmp->lchild = que.top() ; que.pop() ;
        tmp->rchild = que.top() ; que.pop() ;
        tmp->num = tmp->lchild->num + tmp->rchild->num ;
        que.push(tmp) ;
    }
    return que.top() ;
}

TreeNode* createMaxHeap(std::vector<int> &nums) {
    std::priority_queue<int> Max_que ;
    std::queue<TreeNode*> que ;
    for(auto num : nums)  Max_que.push(num) ;
    TreeNode *root = new TreeNode(Max_que.top()); Max_que.pop() ;
    que.push(root) ;
    while(!Max_que.empty()) {
        TreeNode *current = que.front() ; que.pop() ;
        current->lchild = new TreeNode(Max_que.top()) ; Max_que.pop() ;
        if(!Max_que.empty()) {
            current->rchild = new TreeNode(Max_que.top()) ; Max_que.pop() ;
        }
        que.push(current->lchild) ; que.push(current->rchild) ;
    }
    return root ;
}

TreeNode* createMinHeap(std::vector<int> &nums) {
    std::priority_queue<int , std::vector<int> , std::greater<int>> Min_que ;
    std::queue<TreeNode*> que ;
    for(auto num : nums)  Min_que.push(num) ;
    TreeNode *root = new TreeNode(Min_que.top()); Min_que.pop() ;
    que.push(root) ;
    while(!Min_que.empty()) {
        TreeNode *current = que.front() ; que.pop() ;
        current->lchild = new TreeNode(Min_que.top()) ; Min_que.pop() ;
        if(!Min_que.empty()) {
            current->rchild = new TreeNode(Min_que.top()) ; Min_que.pop() ;
        }
        que.push(current->lchild) ; que.push(current->rchild) ;
    }
    return root ;
}

TreeNode* createRandomBinTree(int n , std::vector<std::string> &data) {
    if(n == 0) return nullptr ;
    TreeNode *root = new TreeNode(data.back()) ; data.pop_back() ;
    int leftN =  QRandomGenerator::global()->bounded(n);
    root->lchild = createRandomBinTree(leftN , data) ;
    root->rchild = createRandomBinTree(n - leftN - 1 , data) ;
    return root ;
}

void DestoryTree(TreeNode *root) {
    if(root) {
        TreeNode* left = root->lchild ;
        TreeNode* right = root->rchild ;
        delete  root ;
        if(left) DestoryTree(left) ;
        if(right) DestoryTree(right) ;
    }
}

void createGraphvizDot(TreeNode* &T){
    std::ofstream outFile ;
    outFile.open(SaveDotPathConst.toStdString()  + "Tree.dot") ;
    outFile << ("graph g{\n");
    outFile << ("\tsize=\"6,8!\"\n");
    outFile << ("\tnode [shape=circle,fontsize=25,penwidth=3,fontname=\"Times New Roman, Bold\",margin=\"0.04,0.02\"]\n");
    outFile << ("\tedge[fontsize=25,penwidth=3,fontname=\"Times New Roman, Bold\"]\n");

    std::queue<TreeNode*> que;

    que.push(T);
    int cnt = 1;
    T->height = 1;
    if(T->value.size() == 0)
        outFile << "\t"<<cnt<<"[label="<<T->num<<"]\n" ;
    else
        outFile << "\t"<<cnt<<"[label="<<T->value<<"]\n" ;

    while(!que.empty()) {
        TreeNode* x = que.front();
        que.pop();
        cnt++;

        //sometimes it should be swithched off
        if(x->lchild == NULL && x->rchild == NULL)
            continue;

        if(x->lchild != NULL) {
            if(x->lchild->value.size() == 0)
                outFile<<"\t"<<cnt<<"[label="<<x->lchild->num<<"]\n" ;
            else
                outFile<<"\t"<<cnt<<"[label="<<x->lchild->value<<"]\n" ;

            x->lchild->height = cnt;
            outFile<<"\t"<<x->height<<"--"<<cnt<<std::endl ;
            que.push(x->lchild);
        } else {
            outFile<<"\t"<<cnt<<"[style=invis]\n" ;
            outFile<<"\t"<<x->height<<"--"<<cnt<<" [style=invis]\n" ;
        }
        outFile<<"\t"<<++cnt<<"[style=invis]\n" ;
        outFile<<"\t"<<x->height<<"--"<<cnt<<"[weight=100 style=invis]\n" ;

        cnt++;
        if(x->rchild != NULL) {
            if(x->rchild->value.size() == 0)
                outFile<<"\t"<<cnt<<"[label="<<x->rchild->num<<"]\n" ;
            else
                outFile<<"\t"<<cnt<<"[label="<<x->rchild->value<<"]\n" ;
            x->rchild->height = cnt;
            outFile<<"\t"<<x->height<<"--"<<cnt<<std::endl ;
            que.push(x->rchild);
        } else {
            outFile<<"\t"<<cnt<<"[style=invis]\n" ;
            outFile<<"\t"<<x->height<<"--"<<cnt<<" [style=invis]\n" ;
        }

    }
    outFile<<("}\n");
    outFile.close() ;
}

void String_To_Numbers(std::vector<int>&nums , const std::string str_data) {
    int tmp_num = 0 , flag = 0 , zhengfu = 1;
    for(size_t i = 0 ; i < str_data.size() ; ++i) {
        if(str_data[i] == ' ' && flag == 0) continue ; // 防止用户不小心多打了空格
        if(str_data[i] == '-') {zhengfu = -1 ; continue ;}
        if(str_data[i] == ' '){
            nums.push_back(tmp_num * zhengfu) ;
            flag = 0 ; tmp_num = 0 ; zhengfu = 1 ; continue ;
        }
        tmp_num = tmp_num*10 + str_data[i] - '0' ;
        flag = 1 ;
    }
    // last one
    if(flag == 1) nums.push_back(tmp_num * zhengfu) ;
}

#endif // CREATETREE_H
