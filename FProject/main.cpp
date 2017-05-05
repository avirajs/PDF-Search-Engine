#include <string>
#include <iostream>
#include "searchengine.h"
#include "DocumentParser.h"
using namespace std;
int main()
{
    //keep track of document names if new document is not in add it to inverted file index
// se.addDocumentsToIndex("/home/coder/Documents/sampleCorpus/");
    SearchEngine se;
    se.clearHistory();
//se.addToHistory("AND big boy");
    //se.addBookmark("book","query");

   // se.clear();
 //   se.addDocumentsToIndex("/home/coder/Documents/sampleCorpus/");
    //se.addDocumentsToIndex("/home/coder/Documents/corpus/");
     //se.chooseStructure('H');
    //se.display_search_results("AND Boston Seattle");

/*
    string query;
    string path;
    char d='1';
    char r;
    char s;
    char t;
    char k;
    cout<<"Press 0 to exit"<<endl;
    while(d!='0')
    {
        cout<<"Press m to enter maintainence mode or q for querying and 0 to exit"<<endl;
        cin>>d;
      if(d=='m')
      {
          cout<<"Press a to add document and c to clear"<<endl;
          cin>>r;
          if(r=='a')
          {
              cout<<"Enter document path:"<<endl;
              cin>>query;
              se.addDocumentsToIndex(query);
          }
          else if(r=='c')
          {
              se.clear();
              cout<<"Cleared"<<endl;
          }
      }
      else if(d=='q')
      {
           cout<<"Press H to use hashtable and A for AVL tree"<<endl;
           cin>>s;
          if(s=='H')
            se.chooseStructure('H');
          else if(s=='A')
            se.chooseStructure('A');

          cout<<"Enter query:"<<endl;
          cin>>query;
            se.display_search_results(query);

            cout<<"Do you wish to see the document text from one pdf?" <<endl;
            cout<<"Enter y for yes n for no"<<endl;
            cin>>t;
            if(t=='y')
            {
                cout << "Please enter in the path to the file." << endl;
                cin >> path;
                se.displayRawFile(path);

            }

            continue;

      }

    }
*/

/*
    for(string word:se.topfifty())
        cout<<word<<endl;
    cout<<"total words indexed: "<<se.numWordsIndexed()<<endl;
    cout<<endl;
*/

    //se.clearIndex();

    // tester.writeIndex();
    //tester.readIndex();
    //cout << "It might have worked." << endl;
    /*
    se.display_search_results("Boston");
    se.display_search_results("AND programming computer java");
    se.display_search_results("OR Boston Seattle");
    se.display_search_results("AND book Boston Not Seattle");
    se.display_search_results("Boston NOT Seattle");
*/

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
