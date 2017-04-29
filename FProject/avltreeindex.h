#ifndef AVLTREEINDEX_H
#define AVLTREEINDEX_H

#endif // AVLTREEINDEX_H
#include<iostream>
#include "indexinterface.cpp"
#include <algorithm>
using namespace std;
struct index_node
{
    string word_key;
    index_node* left;
    index_node* right;
    vector<document>documents;
    int height;
};

class AVLTreeIndex : public IndexInterface
{
private:

    index_node* root;

    void makeEmpty(index_node* t);

    index_node* insert(string x,string docname, index_node* t);

    index_node* singleRightRotate(index_node* &t);

    index_node* singleLeftRotate(index_node* &t);

    index_node* doubleLeftRotate(index_node* &t);

    index_node* doubleRightRotate(index_node* &t);

    index_node* findMin(index_node* t);

    index_node* findMax(index_node* t);

    index_node* remove(string x, index_node* t);

    int height(index_node* t);
    int getBalance(index_node* t);
    void inorder(index_node* t);

public:
    AVLTreeIndex();
    virtual vector<document>* findIndex(string key) ; // Pure virtual function makes
    virtual void addIndex(string& word, string& doc);
    void insert(string x,string docname);
    void remove(string x);
    virtual void display();
};
