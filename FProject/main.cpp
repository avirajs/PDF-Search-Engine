#include <string>
#include <iostream>
#include "searchengine.h"
#include "DocumentParser.h"
using namespace std;
int main()
{   //check out self-efficacy in the stemmer it appears on pdf 2 with a space at the end but the stemmer
    //messes it up and changes it to self-efficaci
    //cout << "Hello World!" << endl;
//keep track of document names if new document is not in add it to inverted file index

    //  FileExtractor extractor;
    //  string path = "/home/coder/Documents/Corpus01/sampleCorpus/";
    //  extractor.extract(path);

   SearchEngine se('A');
//se.clearIndex();
   //SearchEngine se("/home/coder/Documents/sampleCorpus/",'A');
   // tester.writeIndex();
   //tester.readIndex();
    //cout << "It might have worked." << endl;
   se.display_search_results("OR Boston results");
    //se.writeIndex();
    //se.querySearch("Boston");
    //se.querySearch("Seattle");
    //se.querySearch("OR Boston Seattle");
    //se.querySearch("AND Boston Seattle");
    //se.querySearch("Boston NOT Seattle");
    //se.querySearch("Boston NOT Seattle Bandura");
    //se.querySearch("AND Boston Seattle NOT Bandura");

    // se.querySearch("AND Boston Seattle");
    // se.querySearch("AND Boston Seattle Altemeyer");



    //se.querySearch("hi how a are you");

    /*
    cout<<" In mainNow"<<endl;
    se.search("innovation");
    se.search("Kalichman");

    se.search("self-efficacy");
    se.search("openness");
    se.search("results");
    se.search("lose");
   se.search("uncertainty");
    se.search("situation");
    se.search("Japanese");*/

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
    vector<document>l;
    document temp("doc2");
    temp.count++;
    l.push_back(temp);

    document tem("doc4");
    tem.count++;
    l.push_back(tem);

    vector<document>r;

    document tm("doc2");
    tm.count++;
    r.push_back(tm);


for(document doc: se.getDifference(l,r))
{
    cout<<doc.docname;
}
*/
