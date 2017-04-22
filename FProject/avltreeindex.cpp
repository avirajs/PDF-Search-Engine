#include "avltreeindex.h"

AVLTreeIndex::AVLTreeIndex()
{
    root=nullptr;
}
AVLTreeIndex::~AVLTreeIndex()
{
    ClearTree(root);
}
void AVLTreeIndex::ClearTree(AVLIndexNode *n)
{
   if(n != NULL)
   {
      ClearTree(n->left);   // Recursively clear the left sub-tree
      ClearTree(n->right);   // Recursively clear the right sub-tree
      delete n;         // Delete this node
   }
}
void  AVLTreeIndex::addIndex(string word, int doc)
{
    //new Index make a new node with that one doc
    set<int>* found=findIndex(word);
    if (found==nullptr)
        root=insert(root,word,doc);
    else//add to set
        found->insert(doc);
}
AVLIndexNode *AVLTreeIndex::insert(AVLIndexNode *root, string value,int docnum)
{

    if (root == NULL)
    {
        root = new AVLIndexNode;
        root->wordkey = value;
        root->docnums.insert(docnum);
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->wordkey)
    {
        root->left = insert(root->left, value,docnum);
        root = balance (root);
    }
    else if (value >= root->wordkey)
    {
        root->right = insert(root->right, value,docnum);
        root = balance (root);
    }
    return root;

}
set<int>* AVLTreeIndex::findIndex(string wordkey)
{

    AVLIndexNode *temp=root;      //'head' is pointer to root node

      while(temp!=nullptr)
      {

        if(wordkey>temp->wordkey)
            temp=temp->right;
        else if(wordkey<temp->wordkey)
            temp=temp->left;
        else if(temp->wordkey==wordkey)
            return &temp->docnums;

      }
      if(temp==nullptr)
          return nullptr;
      else if(temp->wordkey==wordkey)
          return &(temp->docnums);
}
void AVLTreeIndex::inorder(AVLIndexNode *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->wordkey<<"  ";
    inorder (tree->right);
}



int AVLTreeIndex::height(AVLIndexNode *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int AVLTreeIndex::diff(AVLIndexNode *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
AVLIndexNode *AVLTreeIndex::rr_rotation(AVLIndexNode *parent)
{
    AVLIndexNode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
AVLIndexNode *AVLTreeIndex::ll_rotation(AVLIndexNode *parent)
{
    AVLIndexNode *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
AVLIndexNode *AVLTreeIndex::lr_rotation(AVLIndexNode *parent)
{
    AVLIndexNode *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
AVLIndexNode *AVLTreeIndex::rl_rotation(AVLIndexNode *parent)
{
    AVLIndexNode *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
AVLIndexNode *AVLTreeIndex::balance(AVLIndexNode *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}
void AVLTreeIndex::display( )
{
    inorder(root);
}
