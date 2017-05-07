/**
    CSE 2341 AVLTreeIndex.h
    @brief The AVLTreeindex is the custom implementation of the AVLTree.
    The code was based off of github implementation
    https://gist.github.com/harish-r/097688ac7f48bcbadfa5
    @author Aviraj Sinha (owner)
    @version 1.0 05/07/17
*/

#ifndef AVLTREEINDEX_H
#define AVLTREEINDEX_H

#endif // AVLTREEINDEX_H
#include<iostream>
#include "indexinterface.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
using namespace std;

/**
 * @brief The index_node struct allows for storage of inverted indices
 * with other data in tree; most importantly the documents it is found in
 */
struct index_node {
    string word_key;
    index_node* left;
    index_node* right;
    vector<document>documents;
    int height;
};

/**
 * @brief The AVLTreeIndex class case multiple custom insert methods
 * to allow it to either insert from inverted index or directly from parser
 */
class AVLTreeIndex : public IndexInterface {
private:
    vector<document> allwords;//not actually a document just a word and its count

    index_node* root;

    void makeEmpty(index_node* t);

    index_node* insert(string x,string docname, index_node* t);

    index_node* insert(string x,string docname,int doc_count, index_node* t);

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
    void write_inorder(index_node* t);



public:
    AVLTreeIndex();
    ~AVLTreeIndex();
    virtual vector<document>* findIndex(string key);
    virtual void addIndex(string& word, string& doc);
    void insert(string x,string docname);
    void insert(string x,string docname,int count);
    void remove(string x);
    virtual void display();
    virtual void readIndex();
    virtual void writeIndex();
    virtual vector<document>topwords();
    virtual int totalWordsIndexed();
    vector<std::string> split(const std::string &s, char delim);
};
