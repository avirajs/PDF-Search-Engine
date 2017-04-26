#ifndef DocumentParser_H
#define DocumentParser_H

#include "textextractor.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "indexhandler.h"
#include "indexextractor.h"

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

public:
    vector<TextExtractor> m;
    vector <string> k;
    DocumentParser(IndexHandler*);
    string getStemmed(string);
    bool isStopWord(string);
    void extract(string);
};

#endif // DocumentParser_H
