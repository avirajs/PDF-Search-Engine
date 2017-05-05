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
    SearchEngine(string docpath,char);
    SearchEngine();
    void display_search_results(string word);
    void relevencySort(vector<document>& );
    void writeIndex();
    void readIndex();
    void clearIndex();
    int getTotalPages();
    int numWordsIndexed();
    vector<string> topfifty();
    void addDocumentsToIndex(string docpath);
    void chooseStructure(char type);
    void findTDIFs(vector<document>& currdocs);
    void readTotalPages();
    void clearTotalPages();
    void clearWordTxt();
    void clear();
    void displayRawFile(string filePath);
};

#endif // SEARCHENGINE_H
