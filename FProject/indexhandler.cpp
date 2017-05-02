#include "indexhandler.h"

IndexHandler::IndexHandler()
{
    //add other option using arguments
    index=new AVLTreeIndex;
    //index=new hashy;
    //index->writeIndex();

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
