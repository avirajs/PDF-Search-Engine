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
   qe=new QueryEngine(ih,dp);

}

SearchEngine::SearchEngine(string docpath,char type)
{
    //inialize
    ih= new IndexHandler(type);
    dp = new DocumentParser(ih);

    dp->extract(docpath);
    qe=new QueryEngine(ih,dp);

}
void SearchEngine::search(string word)
{
    qe->querySearch(word);
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
