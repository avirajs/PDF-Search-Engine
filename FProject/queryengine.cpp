#include "queryengine.h"

QueryEngine::QueryEngine(IndexHandler *i,DocumentParser*d)
{
    ih=i;
    dp=d;
}
vector<document> QueryEngine::querySearch(string query)
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




    return currdocs;

}
vector<document> QueryEngine::search(string word)
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

}
vector<document>  QueryEngine::getIntersection(vector<document> l,vector<document> r)
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
vector<document> QueryEngine::getUnion(vector<document> l,vector<document> r)
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
vector<document> QueryEngine::getDifference(vector<document> r,vector<document> l)
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
void QueryEngine::findTDIFs(vector<document>& currdocs)
{
    int corpus_sum=0;
    for (unsigned j=0; j<currdocs.size(); j++)
    {
       corpus_sum+= currdocs.at(j).count;
    }
    for(document &doc: currdocs)
    {
        doc.tdif=log(1.*dp->wordy.size()/currdocs.size())*(1.*doc.count/dp->wordy[doc.docname]);
    }

}
void QueryEngine::relevencySort(vector<document>& currdocs)
{

    sort( currdocs.begin( ), currdocs.end( ), [ ]( const document& lhs, const document& rhs )
    {
       return lhs.tdif> rhs.tdif;
    });

}

