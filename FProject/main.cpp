#include <string>
#include <iostream>
#include "searchengine.h"
#include "fileextractor.h"
using namespace std;
int main()
{
    cout << "Hello World!" << endl;


    SearchEngine se("/home/coder/Documents/sampleCorpus/");


    cout<<"search 1\n\n"<<endl;
    se.search("Educators");
    se.search("fontenot");
    se.search("in");
    se.search("uncertainty");
    se.search("results");
    se.search("respond");
     se.search("correspond");
             // se.search("respond")
    //se.search("self-efficacy");
}


//#include "english_stem.h"

//#include "documentparser.h"
//include "indexhandler.h"
//DocumentParser a("stopwords.txt");
/*
IndexHandler ex;
//a.frequentTerm("cs",5);
ex.addIndex("cs","asdf");//parse into index handler
//a.frequentTerm("cs",3);
ex.addIndex("cs","asdf");//parse into index handler

cout<<"set:"<<endl;
for(string doc: (ex.getDocs("cs")))
{
    cout<<doc<<endl;
}
//cout<<"corpus frequency:"<<endl;
//a.corpusFrequency("cs");
//cout<<"document frequency:"<<endl;
//a.allDocFrequency("cs");
//make a while loop menu
*/
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
