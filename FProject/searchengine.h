#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "indexhandler.h"
#include "DocumentParser.h"
class SearchEngine
{
private:
    DocumentParser *dp;
    IndexHandler* ih;
    ifstream * read;

public:
    SearchEngine(string docpath);
    vector<document> querySearch(string);
    vector<document> getIntersection(vector<document>,vector<document>);
    vector<document> getUnion(vector<document>,vector<document>);
    vector<document> getDifference(vector<document>,vector<document>);
    vector<document> search(string);

};

#endif // SEARCHENGINE_H
