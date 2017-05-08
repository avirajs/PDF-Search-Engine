/**
    CSE 2341 IndexExtractor.cpp
    @brief The IndexExtractor class stems the words and removes stopwords.
    The code makes use of the ..........
    @author Aviraj Shina (owner)
    @version 1.0 05/07/17
*/

#include "indexextractor.h"

/**
 * @brief indexextractor::indexextractor This class is repsonsible for stemming and stop words
 */
indexextractor::indexextractor(string stoptxt) {
    useStopWords(stoptxt);
    (*read).close();
}

/**
 * @brief indexextractor::useStopWords adds the stop words from a file
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
 * @brief indexextractor::isStopWord This checks if it is in the stop words set
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
 * @brief indexextractor::getStemmed This gets the stemmed version of the word
 */
string indexextractor::getStemmed(string& w) {

    wstring word(w.begin(),w.end());
    english_stem<> StemEnglish;
    StemEnglish(word);
    w=string( word.begin(), word.end() );
    return w;
}
