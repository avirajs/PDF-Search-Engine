#include "indexhandler.h"

IndexHandler::IndexHandler()
{
    //add other option using arguments
    index=new AVLTreeIndex;
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
