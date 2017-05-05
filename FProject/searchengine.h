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
    vector<string>top50;

public:
    int totalPages;
    SearchEngine(char);
    SearchEngine(string docpath,char);
    void display_search_results(string word);
    void relevencySort(vector<document>& );
    void writeIndex();
    void readIndex();
    void clearIndex();
    int getTotalPages();
    int numWordsIndexed();
    vector<string> topfifty();

void findTDIFs(vector<document>& currdocs);
};

#endif // SEARCHENGINE_H
