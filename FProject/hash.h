/**
    CSE 2341 hash.h
    @brief The hashy class is the custom implementation of the HashTable.
    The basic hash parts of the code was based off of the series of videos by Paul Programming.
    @author Parick Yienger (owner)
    @version 1.0 05/07/17
*/
#ifndef HASH_H
#define HASH_H
#include <string>
#include <vector>
#include <iostream>
#include "indexinterface.h"
#include <math.h>
#include <fstream>
#include <regex.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

/**
 * @brief The item struct This is a struct that contains the word, count, and PDFName.
 * It also uses a vector in the top index on the hash table to handle collisions.
 */
struct item {
    string word_key;
    //document has count and name variables
    int count;
    string docName;
    vector<item> vec;
};

/**
 * @brief The hashy class The hashy class has multiple custom insert methods
 * to allow it to either insert from inverted index or directly from parser
 */
class hashy : public IndexInterface {
public:

    hashy();
    int Hashy(string key);
    void addIndex(string &word, string &name);
    int NumItemsInIndex(int index);
    void display();
    void displayIndex(int index);
    vector<document>* findIndex(string word);
    virtual void readIndex();
    virtual void writeIndex();
    virtual void insertFromFile(string& word, string& doc, int &count);
    vector<std::string> split(const std::string &s, char delim);
    virtual vector<document>topwords();
    virtual int totalWordsIndexed();
private:
    vector<document>allwords;
    static const int tableSize = 1000000;
    item* HashTable[tableSize];

};

#endif // HASH_H
