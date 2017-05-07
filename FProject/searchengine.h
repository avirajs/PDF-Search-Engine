/**
    CSE 2341 SearchEngine.h
    @brief The SearchEngine class uses the various class to create a PDF Search Engine.
    The class makes use of the DocumentParser, IndexHandler, and QueryEngie class to perform
    all of the various tasks of the Mantience mode and Query mode of the user interface.
    @author Aviraj Shina (owner)
    @author Patrick Yienger
    @version 1.0 05/07/17
*/
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "indexhandler.h"
#include "DocumentParser.h"
#include "queryengine.h"
#include <ctime>
#include <iostream>
using namespace std;

/**
 * @brief The bookmark struct This struct uses two strings, one for the PDF name, the other for the query.
 */
struct bookmark {
    bookmark(string m, string q) {
        mark =m;
        query =q;
    }
    string mark;
    string query;
};


/**
 * @brief The SearchEngine class
 */
class SearchEngine {
private:
    DocumentParser *dp;
    IndexHandler* ih;
    QueryEngine* qe;
    vector<document>top50;
    string filePath = "";
    bool flag = false;
    vector<bookmark>bookmarks;

public:
    int totalPages =0;
    SearchEngine(string docpath,char);
    SearchEngine();
    vector<document> display_search_results(string word);
    void relevencySort(vector<document>& );
    void writeIndex();
    void readIndex();
    void clearIndex();
    int getTotalPages();
    int numWordsIndexed();
    vector<document> topfifty();
    bool addDocumentsToIndex(string docpath);
    void chooseStructure(char type);
    void findTDIFs(vector<document>& currdocs);
    int readTotalPages();
    void clearTotalPages();
    void clearWordTxt();
    void clear();
    bool displayRawFile(string filePath);
    void displayTop50();
    void writeFilePathToTXTFile();
    vector<string> readFilePathFromTXTFile();
    void clearFilePath();
    void writeBookmark(string book,string query);
    void readBookmarks();
    void addBookmark(string book,string query);
    void addToHistory(string query);
    void clearHistory();
    void displayHistory();
    void clearBookmarks();
    vector<bookmark> displayBookmarks();

};

#endif // SEARCHENGINE_H
