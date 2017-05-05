#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "indexhandler.h"
#include "DocumentParser.h"
#include "queryengine.h"
#include <ctime>
#include <iostream>
using namespace std;
struct bookmark
{
    bookmark(string m, string q)
    {
        mark=m;
        query=q;
    }
    string mark;
    string query;
};
class SearchEngine
{

private:
    DocumentParser *dp;
    IndexHandler* ih;
    QueryEngine* qe;
    vector<document>top50;
     vector<bookmark>bookmarks;

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
    vector<document> topfifty();
    void addDocumentsToIndex(string docpath);
    void chooseStructure(char type);
    void findTDIFs(vector<document>& currdocs);
    void readTotalPages();
    void clearTotalPages();
    void clearWordTxt();
    void clear();
    void displayRawFile(string filePath);
    void writeBookmark(string book,string query);
    void readBookmarks();
    void addBookmark(string book,string query);
    void addToHistory(string query);
void clearHistory();
    void displayHistory();

    void displayTop50();
void clearBookmarks();
    vector<bookmark> displayBookmarks();

};

#endif // SEARCHENGINE_H
