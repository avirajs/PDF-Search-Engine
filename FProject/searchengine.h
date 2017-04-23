#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "indexhandler.h"
#include "documentparser.h"

class SearchEngine
{
private:
    DocumentParser *dp;
    IndexHandler* ih;
    ifstream * read;

public:
    SearchEngine(string docpath);
    void search(string);

};

#endif // SEARCHENGINE_H
