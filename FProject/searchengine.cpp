#include "searchengine.h"
#include "DocumentParser.h"
#include <algorithm>
#include <iomanip>
#include <stack>

//read from inverted index without parsing
SearchEngine::SearchEngine(char type)
{
   ih= new IndexHandler(type);
   dp=new DocumentParser();
   dp->readInWordyMap();
   qe=new QueryEngine(ih,dp);

    this->readIndex();
}

SearchEngine::SearchEngine(string docpath,char type)
{
    //inialize
    ih= new IndexHandler(type);
    dp = new DocumentParser(ih);
    dp->extract(docpath);
    qe=new QueryEngine(ih,dp);
    this->clearIndex();
    this->writeIndex();

}
void SearchEngine::display_search_results(string word)
{
    vector<document> doc_results=qe->querySearch(word);
    for(int i=0;i<15;i++)
        cout<<"name: "<<doc_results[i].docname<<" count: "<<doc_results[i].count<<" tdif: "<<doc_results[i].tdif<<endl;
}
void SearchEngine::writeIndex()
{
 ih->writeIndex();
}

void SearchEngine::readIndex()
{
    ih->readIndex();
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
int SearchEngine::getTotalPages()
{
    totalPages = dp->getTotalPages();
    ofstream fout("total_pages.txt");
    fout<<totalPages;
    return totalPages;
}
