#include "searchengine.h"

SearchEngine::SearchEngine(string docpath)
{
    dp = new DocumentParser("stopwords.txt");

    /*
    string currdocname;
    string currword;
    //check if stop word
    if(dp->isStopWord(currword))
        continue;
    else
        ih.addIndex(currword,currdocname);*/

}
void SearchEngine::search(string word)
{
   for(string docs: ih.getDocs(word))
   {
       cout<<docs<<endl;
   }
}
