#include "searchengine.h"
#include "DocumentParser.h"
#include <algorithm>
#include <iomanip>
#include <stack>
SearchEngine::SearchEngine(string docpath)
{
    //inialize
    ih= new IndexHandler;
    dp = new DocumentParser(ih);
    read=new ifstream(docpath);
    dp->extract(docpath);

}
vector<document> SearchEngine::querySearch(string query)
{
    istringstream iss(query);
    vector<string> words{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    queue<string> searches;
    for(string word: words)
        searches.push(word);





    bool a=false;
    bool o=false;
    bool n=false;

    vector<document> currdocs;

    //simple search
    if(words.size()==1)
    {
       currdocs= search(words[0]);
       findTDIFs(currdocs);
       relevencySort(currdocs);
       cout<<"\nQuery results:"<<endl;
       for(document doc: currdocs)
          cout<<"name: "<<doc.docname<<" count: "<<doc.count<<" tdif: "<<doc.tdif<<endl;
       return currdocs;
    }

    while(!searches.empty())
    {

       if(searches.front()=="AND")
       {
           a=true;
           o, n=false;
           searches.pop();
       }
       else if(searches.front()=="OR")
       {
           o=true;
           a, n=false;
           searches.pop();
       }
       else if(searches.front()=="NOT")
       {
           n=true;
           o, a=false;
           searches.pop();
       }
       else if(a)
       {
           if(currdocs.empty())
           {
               string temp=searches.front();
               searches.pop();
               currdocs=getIntersection(search(temp),search(searches.front()));
                searches.pop();
           }
           else
           {
                currdocs=getIntersection(currdocs,search(searches.front()));
                searches.pop();
           }
       }
       else if(o)
       {
           if(currdocs.empty())
           {
               string temp=searches.front();
               searches.pop();
               currdocs=getUnion(search(temp),search(searches.front()));

                searches.pop();
           }
           else
           {
                currdocs=getUnion(currdocs,search(searches.front()));
                searches.pop();
           }
       }
       else if(n)
       {
           //should never be empty
           if(!currdocs.empty())
           {
               currdocs=getDifference(currdocs,search(searches.front()));
               searches.pop();
           }
       }
       else//NOT case with word a in front     a NOT b
       {
            currdocs=search(searches.front());
            searches.pop();
       }
    }
    relevencySort(currdocs);

    cout<<"\nQuery results:"<<endl;
    for(document doc: currdocs)
        cout<<"name: "<<doc.docname<<" count: "<<doc.count<<" tdif: "<<doc.tdif<<endl;

    return currdocs;

}
vector<document> SearchEngine::search(string word)
{
    vector<document>*found;
   // cout<<"Document titles containing "<<word<<":"<<endl;
    if(dp->isStopWord(word))
    {
        found=new vector<document>();
        cout<<word<<" is a stop word"<<endl;
        return *found;
    }
    else
    {
        string stem=(dp->getStemmed(word));
        found=ih->getDocs(stem);
        if(found!=nullptr)
        {
            return *found;
        }
        else
        {
            found=new vector<document>();
            cout<<"No documents found"<<endl;
            return *found;
        }
    }

    cout<<endl;
    /*
    cout<<"Document titles containing "<<word<<":"<<endl;
    if(dp->isStopWord(word))
    {
        cout<<word<<" is a stop word"<<endl;
    }
    else
    {
        string stem=(dp->getStemmed(word));
        vector<document>* found= ih->getDocs(stem);
        if(found!=nullptr)
        {
            for(document doc: *(found))
            {
                cout<<"name: "<<setw(60)<<doc.docname<<"count: "<<doc.count<<endl;
            }
        }
        else
        {
            cout<<"No documents found"<<endl;
        }
    }

    cout<<endl;
    */
}
vector<document>  SearchEngine::getIntersection(vector<document> l,vector<document> r)
{
    findTDIFs(l);
    findTDIFs(r);
    vector<document> doc_intersection;
    for(document doc:r)
    {
        //searches for rhs words in left vector
        auto it = find_if(l.begin(), l.end(), [&doc]( document& obj) {return obj.getName() == doc.docname;});
        if (it != l.end())
        {
            doc.count+=(*it).count;
            doc.tdif+=(*it).tdif;
            doc_intersection.push_back(doc);
        }
    }
    return doc_intersection;

}
vector<document> SearchEngine::getUnion(vector<document> l,vector<document> r)
{

    //searches for rhs words in left vector
    findTDIFs(l);
    findTDIFs(r);
    for(document doc:r)
    {
        auto it = find_if(l.begin(), l.end(), [&doc]( document& obj) {return obj.getName() == doc.docname;});
        if (it == l.end())
        {
            l.push_back(doc);
        }
        if (it != l.end())
        {
            (*it).count+=doc.count;
            (*it).tdif+=doc.tdif;
        }
    }
    return l;
}
vector<document> SearchEngine::getDifference(vector<document> r,vector<document> l)
{
    findTDIFs(l);
    findTDIFs(r);
    vector<document> doc_diff;
    for(document doc:r)
    {
        //searches for rhs words in left vector
        auto it = find_if(l.begin(), l.end(), [&doc]( document& obj) {return obj.getName() == doc.docname;});
        if (it == l.end())
        {
               doc_diff.push_back(doc);
        }
    }
    return doc_diff;
}
void SearchEngine::findTDIFs(vector<document>& currdocs)
{
    int corpus_sum=0;
    for (unsigned j=0; j<currdocs.size(); j++)
    {
       corpus_sum+= currdocs.at(j).count;
    }
    for(document &doc: currdocs)
    {
        doc.tdif=(1.*doc.count)/corpus_sum;
    }

}
void SearchEngine::relevencySort(vector<document>& currdocs)
{

    sort( currdocs.begin( ), currdocs.end( ), [ ]( const document& lhs, const document& rhs )
    {
       return lhs.tdif> rhs.tdif;
    });

}
