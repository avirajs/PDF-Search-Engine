/**
    CSE 2341 IndexExtractor.cpp
    @brief The IndexExtractor class stems the words and removes stopwords.
    The code makes use of the ..........
    @author Aviraj Shina (owner)
    @version 1.0 05/07/17
*/

#include "indexextractor.h"

/**
 * @brief indexextractor::indexextractor This .......
 * @param stoptxt The ......
 */
indexextractor::indexextractor(string stoptxt) {
    useStopWords(stoptxt);
    (*read).close();
}

/**
 * @brief indexextractor::useStopWords This .......
 * @param stoptxt The .....
 */
void indexextractor::useStopWords(string stoptxt) {

    string word;
    read=new ifstream(stoptxt);

    if(!(*read)) {
        cout<<stoptxt<<" file did not open"<<endl;
        exit(EXIT_FAILURE);
    }

    while(!(*read).eof()) {

        (*read)>>word;
        stopwords.insert(word);
    }
}

/**
 * @brief indexextractor::isStopWord This .....
 * @param word The .....
 * @return bool The ....
 */
bool indexextractor::isStopWord(string& word) {
    unordered_set<string>::const_iterator got = stopwords.find (word);

    if ( got == stopwords.end() ) {
        //cout << "not a stop word"<<endl;
        return false;
    } else {
        //cout << *got << " is a stop word"<<endl;
        return true;
    }
}

/**
 * @brief indexextractor::displayTermFrequency This ......
 */
void indexextractor::displayTermFrequency() {
    for(auto ii=termfrequencies.begin(); ii!=termfrequencies.end(); ++ii) {
        cout << (*ii).first << ": ";
        vector <documentCount> inVect = (*ii).second;
        for (unsigned j=0; j<inVect.size(); j++) {
            cout <<"doc#:"<< inVect[j].docnum << " count:"<<inVect[j].count<< " ";
        }
        cout << endl;
    }
}

/**
 * @brief indexextractor::allDocFrequency This .......
 * @param word The .......
 */
void indexextractor::allDocFrequency(string word) {
    for(documentCount doc:termfrequencies[word])
        cout<<"doc num: "<<doc.docnum<<" doc count:"<<doc.count<<endl;
}

/**
 * @brief indexextractor::corpusFrequency This .......
 * @param word The ......
 */
void indexextractor::corpusFrequency(string word) {
    vector<documentCount> *v= &termfrequencies[word];

    int sum=0;
    for (unsigned j=0; j<v->size(); j++) {
        sum+= v->at(j).count;
    }
    cout<<"num of words in corpus: "<<sum<<endl;

}

/**
 * @brief indexextractor::getStemmed This .....
 * @param w The ......
 * @return string The .......
 */
string indexextractor::getStemmed(string& w) {

    wstring word(w.begin(),w.end());
    english_stem<> StemEnglish;
    StemEnglish(word);
    w=string( word.begin(), word.end() );
    return w;
}
