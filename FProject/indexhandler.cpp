#include "indexhandler.h"

IndexHandler::IndexHandler()
{
    //add other option using arguments
    index=new AVLTreeIndex;
}
void IndexHandler::addIndex(string word,int docnum)
{
    index->addIndex(word,docnum);
}
set<int>& IndexHandler::getDocs(string word)
{
    return *index->findIndex(word);
}
void IndexHandler::displayIndices()
{
    index->display();
}
