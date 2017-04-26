#include <string>
#include <iostream>
#include "searchengine.h"
#include "DocumentParser.h"
using namespace std;
int main()
{   //check out self-efficacy in the stemmer it appears on pdf 2 with a space at the end but the stemmer
    //messes it up and changes it to self-efficaci
    cout << "Hello World!" << endl;

  //  FileExtractor extractor;
  //  string path = "/home/coder/Documents/Corpus01/sampleCorpus/";
  //  extractor.extract(path);
    SearchEngine se("/home/coder/Documents/large-corpus/");


    cout<<" In mainNow"<<endl;
    se.search("innovation");
    se.search("Kalichman");

    se.search("self-efficacy");
    se.search("openness");
    se.search("results");
    se.search("respond");
     se.search("uncertainty");
             // se.search("respond")
    se.search("Japanese");

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
