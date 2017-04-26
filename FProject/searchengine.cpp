#include "searchengine.h"
#include "DocumentParser.h"
SearchEngine::SearchEngine(string docpath)
{
    //inialize
    ih= new IndexHandler;
    dp = new DocumentParser(ih);

    read=new ifstream(docpath);


    dp->extract(docpath);


    /*
            if(!(dp->isStopWord(word)))
            {
                ih->addIndex(dp->getStemmed(word),pdfName);
            }
    */

/*
    for (int i =0; i < dp->m.size(); i++)
    {
        //The file name is
       string pdfName = dp->k[i];
        for (int j =0; j < dp->m[i].a.size();j++)
        {
            //each word in the pdf is
            string word = dp->m[i].a[j];

            if(!(dp->isStopWord(word)))
            {
                ih->addIndex(dp->getStemmed(word),pdfName);
            }
        }
      //  cout << "Got here: " << i << endl;
    }

*/


}
void SearchEngine::search(string word)
{
    cout<<"Document titles containing "<<word<<":"<<endl;
    if(dp->isStopWord(word))
    {
        cout<<word<<" is a stop word"<<endl;
    }
    else
    {
        string stem=dp->getStemmed(word);
        set<string>* found= ih->getDocs(stem);
        if(found!=nullptr &&found->size()>0)
        {
            for(string docs:*( ih->getDocs(stem)))
            {
                cout<<docs<<endl;
            }
        }
        else
        {
            cout<<"No documents found"<<endl;
        }
    }

    cout<<endl;
}
