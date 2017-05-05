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
   top50= ih->topFifty();

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
    this->readIndex();
    top50=ih->topFifty();

}
void SearchEngine::display_search_results(string word)
{

    cout<<"\nSearching: "<<word<<endl;
    vector<document> doc_results=qe->querySearch(word);
    int cnt=0;
    for(document doc:doc_results)
    {
        cout<<"name: "<<doc.docname<<" count: "<<doc.count<<" tdif: "<<doc.tdif<<endl;
        if(cnt++==15)
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
int SearchEngine::getTotalPages()
{
    totalPages = dp->getTotalPages();
    ofstream fout("total_pages.txt");
    fout<<totalPages;
    return totalPages;
}
