/**
    CSE 2341 DocumentParser.h
    @brief The DocumentParser class parses the PDFs.
    It extracts the text using the TextExtractor class, stems the words and removes
    stop words using the IndexExtractor class, and computes the term frequency using the custom
    AVLTree or the custom Hash table.
    @author Aviraj Sinha (owner)
    @author Patrick Yienger
    @version 1.0 05/07/17
*/
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

/**
 * @brief The DocumentParser class
 */
class DocumentParser {
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
