#include "english_stem.h"
#include <string>
#include <iostream>
#include "documentparser.h"
#include "indexhandler.h"
using namespace std;
int main()
{

   // DocumentParser a("stopwords.txt");
    IndexHandler ex;
    //a.frequentTerm("cs",5);
    ex.addIndex("cs",45);//parse into index handler
    //a.frequentTerm("cs",3);
    ex.addIndex("cs",3);//parse into index handler

    cout<<"set:"<<endl;
    for(int doc: (ex.getDocs("cs")))
    {
        cout<<doc<<endl;
    }
    //cout<<"corpus frequency:"<<endl;
    //a.corpusFrequency("cs");
    //cout<<"document frequency:"<<endl;
    //a.allDocFrequency("cs");
    //make a while loop menu

}
/*
    AVLTreeIndex ex;
    ex.addIndex("cs",3);
    ex.addIndex("cs",4);
    ex.addIndex("cs",5);
    ex.addIndex("beasds",3);*/
    //ex.display();
    //cout<<(ex.findIndex("cs")==nullptr);
    /*
    for(int doc: *(ex.findIndex("cs")))
    {
        cout<<doc<<endl;
    }*/
    //ex.findIndex("yes");
    //ex.display(1);
/*
 *  DocumentParser a("stopwords.txt");
    cout<<a.getStemmed("documentation");
    a.frequentTerm("yes",2);
    a.frequentTerm("yes",5);
    a.frequentTerm("yes",2);
    a.frequentTerm("yes",5);
    a.frequentTerm("yes",2);
    a.frequentTerm("yes",2);
    a.frequentTerm("ye",24);
    a.frequentTerm("no",232);
    a.displayTermFrequency();

    a.docFrequency("yes",2);
    a.corpusFrequency("yes");
*/
