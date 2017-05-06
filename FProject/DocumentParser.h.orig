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
#include "rawoutputextractor.h"
class DocumentParser
{
private:
    vector<rawOutputExtractor> rawVec;
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
    bool flag = false;

public:
    map<string,int> wordy;
    vector<TextExtractor> m;
    vector <string> k;
    DocumentParser(IndexHandler*);
    DocumentParser();
    string getStemmed(string&);
    bool isStopWord(string&);
    bool extract(string);
    int getTotalPages();
    void readInWordyMap();
    int numOfDocs();
    void clearWordTxt();
    bool rawTextExtract(string fileStream);
};

#endif // DocumentParser_H
