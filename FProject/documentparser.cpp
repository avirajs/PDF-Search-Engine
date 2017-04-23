#include "documentparser.h"

DocumentParser::DocumentParser(string stoptxt)
{
    useStopWords(stoptxt);
    (*read).close();
}
void DocumentParser::useStopWords(string stoptxt)
{

    string word;
    read=new ifstream(stoptxt);

    if(!(*read))
    {
        cout<<stoptxt<<" file did not open"<<endl;
        exit(EXIT_FAILURE);
    }

    while(!(*read).eof())
    {

        (*read)>>word;
        stopwords.insert(word);
    }
}
bool DocumentParser::isStopWord(string word)
{
    unordered_set<string>::const_iterator got = stopwords.find (word);

      if ( got == stopwords.end() )
      {
        //cout << "not a stop word"<<endl;
        return false;
      }
      else
      {
        //cout << *got << " is a stop word"<<endl;
        return true;
      }
}
void DocumentParser::frequentTerm(string word,int docnum)
{
    if (termfrequencies.find(word) == termfrequencies.end())
    {
        vector<documentCount> doccount;
        doccount.push_back(documentCount(docnum));
        termfrequencies[word]=doccount;
    }
    else//add word
    {
      vector<documentCount> *v= &termfrequencies[word];
      auto it = find_if(v->begin(), v->end(), [docnum](const documentCount& obj) {return obj.docnum == docnum;});
      if (it != v->end())
        (*it).count++;
      else//add document number
          v->push_back(documentCount(docnum));
    }

}
void DocumentParser::displayTermFrequency()
{
    for(auto ii=termfrequencies.begin(); ii!=termfrequencies.end(); ++ii)
    {
       cout << (*ii).first << ": ";
       vector <documentCount> inVect = (*ii).second;
       for (unsigned j=0; j<inVect.size(); j++)
       {
           cout <<"doc#:"<< inVect[j].docnum << " count:"<<inVect[j].count<< " ";
       }
       cout << endl;
    }
}
void DocumentParser::docFrequency(string word,int docnum)
{
     vector<documentCount> *v= &termfrequencies[word];
    auto it = find_if(v->begin(), v->end(), [docnum](const documentCount& obj) {return obj.docnum == docnum;});
    cout<<(*it).docnum<<" "<<(*it).count<<endl;
}
void DocumentParser::allDocFrequency(string word)
{
    for(documentCount doc:termfrequencies[word])
        cout<<"doc num: "<<doc.docnum<<" doc count:"<<doc.count<<endl;
}
void DocumentParser::corpusFrequency(string word)
{
    vector<documentCount> *v= &termfrequencies[word];

       int sum=0;
       for (unsigned j=0; j<v->size(); j++)
       {
          sum+= v->at(j).count;
       }
       cout<<"num of words in corpus: "<<sum<<endl;

}
string DocumentParser::getStemmed(string w)
{
    wstring word(w.begin(),w.end());
    english_stem<> StemEnglish;
    StemEnglish(word);
    return string( word.begin(), word.end() );
}
