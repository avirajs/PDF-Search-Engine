#include "indexhandler.h"

IndexHandler::IndexHandler(char type)
{
    //add other option using arguments
    if(type=='A')
    {
    index=new AVLTreeIndex;
    }
    else if(type=='H')
        index=new hashy;

}
void IndexHandler::addIndex(string word,string docname)
{
    index->addIndex(word,docname);
}
vector<document>* IndexHandler::getDocs(string word)
{
   return index->findIndex(word);
}
void IndexHandler::displayIndices()
{
    index->display();
}
void IndexHandler::writeIndex()
{
    index->writeIndex();
}
void IndexHandler::readIndex()
{
    index->readIndex();
}
vector<string> IndexHandler::topFifty()
{
 return index->topwords();
}
int IndexHandler::totalWordsIndexed()
{
    return index->totalWordsIndexed();
}
