/**
    CSE 2341 IndexExtractor.h
    @brief The IndexExtractor class stems the words and removes stopwords.
    The code makes use of the ..........
    @author Aviraj Sinha (owner)
    @version 1.0 05/07/17
*/
#ifndef indexextractor_H
#define indexextractor_H
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include "english_stem.h"
#include <algorithm>

using namespace std;
using namespace stemming;

/**
 * @brief The indexextractor class
 */
class indexextractor {
private:
    unordered_set<string>stopwords;
    struct documentCount {
        int docnum;
        int count=1;
        documentCount(int num) {
            docnum=num;
        }
    };
    map<string,vector<documentCount>>termfrequencies;
    ifstream *read;

public:
    indexextractor(string);
    void useStopWords(string);
    bool isStopWord(string&);
    string getStemmed(string&);
};

#endif // indexextractor_H
