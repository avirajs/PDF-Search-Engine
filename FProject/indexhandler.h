/**
    CSE 2341 IndexHandler.h
    @brief The IndexHandler class creates and stores the inverted index file.
    It uses the custom data structures to write and read the inverted index.
    @author Aviraj Sinha (owner)
    @version 1.0 05/07/17
*/
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

/**
 * @brief The IndexHandler class
 */
class IndexHandler {
private:
    IndexInterface *index;
    //index interface pointer
public:
    IndexHandler(char type);
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
