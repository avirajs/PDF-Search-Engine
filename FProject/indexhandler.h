
#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include "indexhandler.h"
#include "avltreeindex.h"
#include "hash.h"
using namespace std;

class IndexHandler
{
private:
    IndexInterface *index;
    //index interface pointer
public:
    IndexHandler(char type);//add argument to decide which data structure to create but for now avl tree
    void writeIndex();
    void addIndex(string,string);
    vector<document>* getDocs(string);
    int getDocumentFrequency(string word, string docname);
    int getCorpusFrequency(string word);
    void displayIndices();
    void readIndex();
    vector<document> topFifty();
    int totalWordsIndexed();
};

#endif // INDEXHANDLER_H
