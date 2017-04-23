#include "searchengine.h"
#include "fileextractor.h"
SearchEngine::SearchEngine(string docpath)
{
    //inialize
    dp = new DocumentParser("stopwords.txt");
    ih= new IndexHandler;
    read=new ifstream(docpath);




    FileExtractor extractor;
    string path = docpath;
    extractor.extract(path);


    for (int i =0; i < extractor.m.size(); i++)
    {
        //The file name is
       string pdfName = extractor.k[i];
        for (int j =0; j < extractor.m[i].a.size();j++)
        {
            //each word in the pdf is
            string word = extractor.m[i].a[j];

            if(!(dp->isStopWord(word)))
            {
                ih->addIndex(dp->getStemmed(word),pdfName);
            }
        }
      //  cout << "Got here: " << i << endl;
    }




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
