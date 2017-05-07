/**
    CSE 2341 IndexHandler.h
    @brief The IndexHandler class creates and stores the inverted index file.
    It uses the custom data structures to write and read the inverted index.
    @author Aviraj Shina (owner)
    @author Patrick Yienger
    @version 1.0 05/07/17
*/

#include "indexhandler.h"

/**
 * @brief IndexHandler::IndexHandler The index handler constructor.
 * This initialaizes the chosen data structure.
 * @param type The data structure to be initalized.
 */
IndexHandler::IndexHandler(char type) {
    //add other option using arguments
    if(type=='A') {
        index=new AVLTreeIndex;
    }

    else if(type=='H')
        index=new hashy;
}

/**
 * @brief IndexHandler::addIndex This adds the word and the PDf name to the chosen data structure.
 * @param word The word to be added.
 * @param docname The PDF name to be added.
 */
void IndexHandler::addIndex(string word,string docname) {
    index->addIndex(word,docname);
}

/**
 * @brief IndexHandler::getDocs This returns the name of all of the PDFs containing the requested word.
 * @param word The word requested.
 * @return vector<document> The vector of document object that stores the count and PDF name of the requested word.
 */
vector<document>* IndexHandler::getDocs(string word) {
    return index->findIndex(word);
}

/**
 * @brief IndexHandler::displayIndices This dispays the indicies of the appropriate data structure.
 */
void IndexHandler::displayIndices() {
    index->display();
}

/**
 * @brief IndexHandler::writeIndex This writes the inverted index file to the .txt file from the appropriate data structure.
 */
void IndexHandler::writeIndex() {
    index->writeIndex();
}

/**
 * @brief IndexHandler::readIndex This reads the data from the inverted index file and into the appropriate data structure.
 */
void IndexHandler::readIndex() {
    index->readIndex();
}

/**
 * @brief IndexHandler::topFifty This returns the top fifty words and their count.
 * @return vector<document> This returns the vector of document objects containing the word and the count.
 */
vector<document> IndexHandler::topFifty() {
    return index->topwords();
}

/**
 * @brief IndexHandler::totalWordsIndexed This returns the total number of words indexed.
 * @return totalWordsIndexed
 */
int IndexHandler::totalWordsIndexed() {
    return index->totalWordsIndexed();
}
