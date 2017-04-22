#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include "english_stem.h"
#include <algorithm>

using namespace std;
using namespace stemming;
class DocumentParser
{
private:
    unordered_set<string>stopwords;
    struct documentCount
    {
        int docnum;
        int count=1;
        documentCount(int num)
        {
            docnum=num;
        }
    };
    map<string,vector<documentCount>>termfrequencies;
    ifstream *read;

public:
    DocumentParser(string);
    void useStopWords(string);
    bool isStopWord(string);
    void frequentTerm(string,int);//later make return * to vector
    void displayTermFrequency();
    void docFrequency(string,int);
    void allDocFrequency(string word);
    void corpusFrequency(string);
    string getStemmed(string);
};

#endif // DOCUMENTPARSER_H
