
#ifndef HASH_H
#define HASH_H
#include <string>
#include <vector>
#include <iostream>
#include "indexinterface.h"


struct item
{
    string word_key;
    //document has count and name variables
    int count;
    string docName;
    vector<item> vec;
};

class hashy : public IndexInterface
{
public:
    hashy();
    int Hashy(string key);
    void addIndex(string &word, string &name);
    int NumItemsInIndex(int index);
    void display();
    void displayIndex(int index);
    vector<document>* findIndex(string word);
private:
    static const int tableSize = 1000000;
    item* HashTable[tableSize];

};

#endif // HASH_H
