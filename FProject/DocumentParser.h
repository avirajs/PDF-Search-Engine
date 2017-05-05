#ifndef DocumentParser_H
#define DocumentParser_H

#include "textextractor.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "indexhandler.h"
#include "indexextractor.h"
#include <map>

class DocumentParser
{
private:
    IndexHandler* ih;
    indexextractor* ie;
    int cDot;
    int cP;
    DIR *pdir = nullptr;
    char name[200];
    char *nn = name;
    int totalPages =0;
    int wordCount;
    string docName;

public:
    map<string,int> wordy;
    vector<TextExtractor> m;
    vector <string> k;
    DocumentParser(IndexHandler*);
    DocumentParser();
    string getStemmed(string&);
    bool isStopWord(string&);
    void extract(string);
    int getTotalPages();
    void readInWordyMap();
    int numOfDocs();
    void clearWordTxt();
};

#endif // DocumentParser_H
