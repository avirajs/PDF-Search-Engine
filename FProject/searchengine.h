#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "indexhandler.h"
#include "DocumentParser.h"
#include "queryengine.h"
class SearchEngine
{
private:
    DocumentParser *dp;
    IndexHandler* ih;
    QueryEngine* qe;

public:
    SearchEngine(char);
    SearchEngine(string docpath,char);
    void search(string word);
    void relevencySort(vector<document>& );
    void writeIndex();
    void readIndex();
    void clearIndex();

void findTDIFs(vector<document>& currdocs);
};

#endif // SEARCHENGINE_H
