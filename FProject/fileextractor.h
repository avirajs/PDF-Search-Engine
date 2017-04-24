#ifndef FILEEXTRACTOR_H
#define FILEEXTRACTOR_H
#include "fileextractor.h"
#include "textextractor.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>


class FileExtractor
{
private:

    int cDot;
    int cP;
    DIR *pdir = nullptr;
    char name[200];
    char *nn = name;

public:
    vector<TextExtractor> m;
    vector <string> k;
    FileExtractor();
    void extract(string);
};

#endif // FILEEXTRACTOR_H
