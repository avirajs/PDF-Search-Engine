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
int IndexHandler::getDocumentFrequency(string word, string docname)
{
   vector<document> *v= getDocs(word);
   auto it = find_if(v->begin(), v->end(), [docname](const document& obj) {return obj.docname == docname;});
   return (*it).count;
}
int IndexHandler::getCorpusFrequency(string word)
{
    vector<document> *v=getDocs(word);

       int sum=0;
       for (unsigned j=0; j<v->size(); j++)
       {
          sum+= v->at(j).count;
       }
       return sum;
       //cout<<"num of words in corpus: "<<sum<<endl;
}
void IndexHandler::displayIndices()
{
    index->display();
}
