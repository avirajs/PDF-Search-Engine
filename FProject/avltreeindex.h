//citation http://www.sanfoundry.com/cpp-program-implement-avl-trees/
#ifndef AVLTreeIndex_H
#define AVLTreeIndex_H
#include "indexinterface.cpp"
#include <iostream>
using namespace std;
struct AVLIndexNode
{
   string wordkey="";
   set<string>docnums;
   // Other data fields can be inserted here
   AVLIndexNode *left=nullptr;
   AVLIndexNode *right=nullptr;
};

class AVLTreeIndex: public IndexInterface
{
   private:
      AVLIndexNode   *root;

   public:
        int height(AVLIndexNode *);
        int diff(AVLIndexNode *);
        virtual set<string>* findIndex(string key);
        virtual void addIndex(string word, string doc);
        AVLTreeIndex();
        ~AVLTreeIndex();
        AVLIndexNode *rr_rotation(AVLIndexNode *);
        AVLIndexNode *ll_rotation(AVLIndexNode *);
        AVLIndexNode *lr_rotation(AVLIndexNode *);
        AVLIndexNode *rl_rotation(AVLIndexNode *);
        AVLIndexNode* balance(AVLIndexNode *);
        AVLIndexNode* insert(AVLIndexNode *,string,string);
        virtual void display();
        void inorder(AVLIndexNode *tree);

   private:
        void ClearTree(AVLIndexNode *n);

};

#endif // AVLTreeIndexIndex_H
