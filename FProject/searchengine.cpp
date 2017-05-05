#include "searchengine.h"
#include "DocumentParser.h"
#include <algorithm>
#include <iomanip>
#include <stack>

//read from inverted index without parsing
void SearchEngine::chooseStructure(char type)
{
   ih= new IndexHandler(type);
   dp=new DocumentParser();
   dp->readInWordyMap();
   qe=new QueryEngine(ih,dp);
   this->readIndex();
   top50= ih->topFifty();
}
SearchEngine::SearchEngine()
{

}
void SearchEngine::addDocumentsToIndex(string docpath)
{
    //create a whole index handler to allow the counts to be stored too
    ih= new IndexHandler('H');
    dp = new DocumentParser(ih);
    dp->extract(docpath);
    this->writeIndex();
    //not clearing
}
void SearchEngine::clear()
{
    this->clearIndex();
    this->clearTotalPages();
    this->clearWordTxt();
}
/*
SearchEngine::SearchEngine(string docpath)
{
    //used only for creating indexes
    ih= new IndexHandler('H');
    dp = new DocumentParser(ih);
    dp->extract(docpath);
    this->clearIndex();
    this->writeIndex();
}*/
void SearchEngine::clearWordTxt()
{
    dp = new DocumentParser();
    dp->clearWordTxt();
}
void SearchEngine::display_search_results(string word)
{

   // cout<<"\nSearching: "<<word<<endl;
    vector<document> doc_results=qe->querySearch(word);
    int cnt=0;
    for(document doc:doc_results)
    {
        cout<<"name: "<<doc.docname<<" count: "<<doc.count<<" tdif: "<<doc.tdif<<endl;
        if(cnt++==14)
            break;
    }
    cout<<endl;
}
int SearchEngine::numWordsIndexed()
{
 return ih->totalWordsIndexed();
}
vector<string> SearchEngine::topfifty()
{
 return top50;
}
int SearchEngine::getTotalPages()
{
    totalPages = dp->getTotalPages();
    ofstream fout("total_pages.txt");
    fout<<totalPages;
    return totalPages;
}
void SearchEngine::readIndex()
{
     ih->readIndex();
}
void SearchEngine::writeIndex()
{
 ih->writeIndex();
}
void SearchEngine::clearIndex()
{
    ofstream fout("inverted_index.txt",ios::out);
    if(!fout)
    {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}
void SearchEngine::readTotalPages()
{
    int pages =0;
    ifstream fin;
    fin.open("total_pages.txt",fstream::app);
    while(!fin.eof())
    {
        fin >> totalPages;
        pages += totalPages;
        totalPages =0;
    }
    cout << "The total page count is: " << pages << endl;
}

void SearchEngine::clearTotalPages()
{
 ofstream ouut("total_pages.txt",ios::out);
 if(!ouut)
 {
     cout<<"clear file cant be opened"<<endl;
     exit(EXIT_FAILURE);
 }
}
void SearchEngine::displayRawFile(string filePath)
{
    ih=new IndexHandler('H');
    dp=new DocumentParser(ih);
    dp->rawTextExtract(filePath);
}
