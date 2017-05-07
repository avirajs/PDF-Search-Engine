/**
    CSE 2341 hash.cpp
    @brief The hashy class is the custom implementation of the HashTable.
    The basic hash parts of the code was based off of the series of videos by Paul Programming.
    @author Parick Yienger (owner)
    @version 1.0 05/07/17
*/

#include "hash.h"

/**
 * @brief hashy::hashy This is the hashy constructor. It sets all of the elements of the HashTable to default values.
 */
hashy::hashy() {
    //sets elements of has table to default valuse
    for (int i =0; i < tableSize; i++) {
        //count docName word_key next
        HashTable[i] = new item;
        HashTable[i]->count = 0;
        HashTable[i]->docName = "empty";
        HashTable[i]->word_key = "empty";
    }
}

/**
 * @brief hashy::Hashy The hash function that retuns the int value of the supplied string.
 * This function is based off of the hash function for strings developed by Paul Larson.
 * @param key The string to be hashed.
 * @return int The integer hash value of the string.
 */
int hashy::Hashy(string key) {
    const char* s = key.c_str();
    int hash = 0;
    while (*s) {
        hash = hash * 101  +  *s++;
    }
    return abs(hash%tableSize);
}

/**
 * @brief hashy::addIndex This adds the supplied word and name to the hash table. It also updates the count.
 * @param word The word to be added.
 * @param name The pdf the word came from.
 */
void hashy::addIndex(string &word, string &name) {
    int index = Hashy(word);
    item* Ptr = HashTable[index];
    //If the index is empty
    if (HashTable[index]->word_key == "empty") {
        HashTable[index]->word_key = word;
        HashTable[index]->count++;
        HashTable[index]->docName = name;
        return;
    }
    //check to see if word already on index and has same doc name, increase count if so
    else {
        int i =0;
        int j = Ptr->vec.size();
        while (i != j) {
            string cword = Ptr->vec[i].word_key;
            string cdocName = Ptr->vec[i].docName;
            if (cword.compare(word) == 0) {
                if(cdocName.compare(name) == 0) {
                    //increase the count for repeat words in the same document
                    Ptr->vec[i].count++;
                    return;
                }
            }
            i++;
        }
    }
    //If none of the above add new element to the vector
    Ptr = HashTable[index];
    item* n = new item;
    n->count = 0;
    n->count++;
    n->docName = name;
    n->word_key = word;
    Ptr->vec.push_back(*n);

}

/**
 * @brief hashy::NumItemsInIndex This returns the number of items in a specified index.
 * @param index The specified index.
 * @return int The number of words in the index.
 */
int hashy::NumItemsInIndex(int index) {
    int counts = 0;
    if (HashTable[index]->word_key == "empty") {
        return counts;
    } else {
        counts++;
        item* Ptr = HashTable[index];
        counts+= Ptr->vec.size();
    }
    return counts;
}

/**
 * @brief hashy::display This displays the contents of the hash table.
 */
void hashy::display() {
    int number;
    for (int i =0; i < tableSize; i++) {
        number = NumItemsInIndex(i);
        cout << "------------------------" << endl;
        cout << "------------------------" << endl;
        cout << "The index is: " << i << endl;
        cout << "The number of items in the index is: " << number << endl;
        cout << "The word is: " << HashTable[i]->word_key << endl;
        cout << "The doc name is: " << HashTable[i]->docName << endl;
        cout << "The count is: " << HashTable[i]->count << endl;
    }
}

/**
 * @brief hashy::displayIndex This displays the cotents oh the hash table at a specified index.
 * @param index The specified index.
 */
void hashy::displayIndex(int index) {
    item* Ptr = HashTable[index];
    if (Ptr->word_key == "empty") {
        cout << "The index is: " << index << endl;
        cout << "The index is empty" << endl;
    } else {
        cout << "The index is: " << index << endl;
        cout << "The number of words in the index is: " << NumItemsInIndex(index) << endl;
        int i =0;
        while(i < Ptr->vec.size()) {
            cout << "------------------------" << endl;
            cout << "------------------------" << endl;
            cout << "The word is: " << Ptr->vec[i].word_key << endl;
            cout << "The doc name is: " << Ptr->vec[i].docName << endl;
            cout << "The count is: " << Ptr->vec[i].count << endl;
            i++;
        }
    }
}

/**
 * @brief hashy::findIndex This finds the index of a specified word.
 * @param word The specified word.
 * @return  vector<document> The vector of document that contains all off the PDF names and counts of the specified word.
 */
vector<document>* hashy::findIndex(string word) {
    int index = Hashy(word);
    vector<document>* data = new vector<document>;
    bool found = false;
    item* Ptr = HashTable[index];
    string cword = Ptr->word_key;
    if (cword.compare(word) == 0) {
        string d = "empty";
        document docs(d);
        int num = Ptr->count;
        string name = Ptr->docName;
        docs.setCount(num);
        docs.setName(name);
        data->push_back(docs);
        found = true;
    }
    int i =0;
    int j = Ptr->vec.size();
    while(i < j) {
        string cword = Ptr->vec[i].word_key;
        if (cword.compare(word) == 0) {
            string d = "empty";
            document docs(d);
            int num = Ptr->vec[i].count;
            string name = Ptr->vec[i].docName;
            docs.setCount(num);
            docs.setName(name);
            data->push_back(docs);
            found = true;
        }
        i++;
    }
    if (found) {
        //data = &list;
        return data;
    } else {
        data = nullptr;
        return data;
    }

}

/**
 * @brief hashy::readIndex This reads the data from the inverted file index and into the hash table.
 */
void hashy::readIndex() {
    ifstream read("inverted_index.txt");
    if (!read) {
        cout << "file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    // cout << "File was opened" << endl;
    string line;

    string wordkey;
    string docname;
    int doccount=0;
//statck overflow citation hwe
    while(!(read.eof())) {
        getline(read,line);
        wordkey=line.substr(0,line.find("-"));

        vector<string> tokens=split(line.substr(line.find("-")+1),'|');

        int wordCorpusCount=0;
        for(int i=0; i<tokens.size(); i+=2) {
            docname=tokens[i];
            doccount=std::stoi(tokens[i+1]);
            // cout<<"word: "<<wordkey<<" doc name: "<<docname<<" count: "<<count<<endl;
            insertFromFile(wordkey,docname,doccount);
            wordCorpusCount+=doccount;
        }
        if(wordkey.size()>3)
            allwords.push_back(document(wordkey,wordCorpusCount));//not actually a document but a word and count
    }

}

/**
 * @brief hashy::totalWordsIndexed This returns the total words indexed.
 * @return The total words indexed.
 */
int hashy::totalWordsIndexed() {
    allwords.size();
}

/**
 * @brief hashy::topwords This finds and returns the top fifty words and their counts.
 * @return vector<document> The vector of documents objects of the top fifty words and their counts.
 */
vector<document>hashy::topwords() {
    nth_element(allwords.begin(), allwords.begin()+49, allwords.end(), [ ]( const document& lhs, const document& rhs ) {
        return lhs.count > rhs.count;
    });

    vector<document>topfifty;
    for(int i=0; i<50; i++)
        topfifty.push_back(document(allwords[i].docname,allwords[i].count));

    sort( topfifty.begin( ), topfifty.end( ), [ ]( const document& lhs, const document& rhs ) {
        return lhs.count> rhs.count;
    });

    return topfifty;


}

/**
 * @brief hashy::writeIndex This writes the inverted file index from the hash table and into the index .txt.
 */
void hashy::writeIndex() {
    ofstream fout;
    fout.open("inverted_index.txt", fstream::app);

    // checks to see if file can open
    if(!fout) {
        cout << "File FlightData can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

    //outer loop that loops through the entire hash table
    for (int i =0; i < tableSize; i++) {
        //at each index of the hash table make new data to store the results to output in
        item* Ptr = HashTable[i];
        vector<vector<document>> wordSet;
        vector<document> wordDocs;
        vector<document> otherWords;
        vector <string> wordCheck;
        string tableWord = Ptr->word_key;
        //add the word from the first index to the vector of different words located at this index
        wordCheck.push_back(tableWord);
        if (tableWord != "empty") {
            //make a document object for the first index and add it to the wordDocs
            string d = "empty";
            document docs(d);
            int num = Ptr->count;
            string name = Ptr->docName;
            docs.setCount(num);
            docs.setName(name);
            //add the new document object to the wordDocs
            wordDocs.push_back(docs);
            //loop through all items in the vector and check to see if they are the same as tableWord, if so make a doc
            //object and add to wordDocs
            int j = Ptr->vec.size();
            for (int i =0; i < j; i++) {
                string cword = Ptr->vec[i].word_key;
                if (cword.compare(tableWord) == 0) {
                    //check to see if from same pdf
                    if (Ptr->vec[i].docName == Ptr->docName) {
                        //add the count variable together
                        wordDocs[i].count+= Ptr->vec[i].count;

                    }
                    //else create a new document object for diff pdf
                    else {
                        string dd = "empty";
                        document ddocs(dd);
                        int num = Ptr->vec[i].count;
                        string name = Ptr->vec[i].docName;
                        ddocs.setCount(num);
                        ddocs.setName(name);
                        //add the new document object to the wordDocs
                        wordDocs.push_back(ddocs);
                    }
                }
            }
            //add the vector<documents> to the vector of vector<documents>
            wordSet.push_back(wordDocs);

            //add it to table of words and search the vector for all words that are the same, if these words are the same,
            //then make a document object for each word and add them to vector of documents, then add the finished vector
            //of documents to the vector of vector of documents
            int jj = Ptr->vec.size();
            for (int i =0; i < jj; i++) {
                bool isAlreadyOnVector = false;
                string cword = Ptr->vec[i].word_key;
                //loop through all element of wordCheck table if it is on the vector set bool flag to true;
                for (int ii =0; ii < wordCheck.size(); ii++) {
                    string compare = wordCheck[ii];
                    if (cword.compare(compare) ==0) {
                        isAlreadyOnVector = true;
                    }
                }
                //if the word is already on
                if (isAlreadyOnVector == true) {
                    //add the word to the string vector
                    ;
                }
                // if word is not already on,search the vector for all words that are the same
                else {
                    wordCheck.push_back(cword);
                    //loop through all words in the vector
                    for (int iii =0; iii < jj; iii++) {
                        //compare the words to the word that was added to the vector of words
                        //if same make a new document object and add to the new vector of documents
                        string nword = Ptr->vec[iii].word_key;
                        if (cword.compare(nword) == 0) {
                            string ddd = "empty";
                            document dddocs(ddd);
                            int num = Ptr->vec[iii].count;
                            string name = Ptr->vec[iii].docName;
                            dddocs.setCount(num);
                            dddocs.setName(name);
                            //add the new document object to the wordDocs
                            otherWords.push_back(dddocs);
                        }
                    }
                    //add the vector<documents> to the vector of vector<documents>
                    wordSet.push_back(otherWords);
                    //reset otherWords
                    otherWords.clear();
                }

            }
            int helpme = 0;
            //loop through the vector<vector<document>>
            for (int i = 0; i < wordSet.size(); i++ ) {

                //at each element write the word vector<documents> and the word to the
                fout << wordCheck[i] <<  "-";
                //cout << wordCheck[i] <<  "-";
                for (int j = 0; j < wordSet[i].size(); j++) {
                    fout << wordSet[i][j].docname << "|" << wordSet[i][j].count << "|";
                    //cout <<  wordSet[i][j].docname << "|" << wordSet[i][j].count << "|";
                }
                fout << endl;
                //cout << endl;
            }
        }
        //reset all vectors
        wordCheck.clear();
        wordDocs.clear();
        wordSet.clear();
        otherWords.clear();


    }//hash table loop
}

/**
 * @brief hashy::insertFromFile This inserts the data from the inverted file index and into the hash table.
 * @param word The word to be inserted.
 * @param doc The PDF name to be inserted.
 * @param count The count to be inserted.
 */
void hashy::insertFromFile(string& word, string& doc, int &count) {
    int index = Hashy(word);
    item* Ptr = HashTable[index];
    //If the index is empty
    if (HashTable[index]->word_key == "empty") {
        HashTable[index]->word_key = word;
        HashTable[index]->count = count;
        HashTable[index]->docName = doc;
        return;
    }
    //If none of the above add new element to the vector
    item* n = new item;
    n->count = count;
    n->docName = doc;
    n->word_key = word;
    Ptr->vec.push_back(*n);
}

/**
 * @brief hashy::split This splits the supplied string by a given delimiter.
 * @param s The string to be split.
 * @param delim The character to be used as the delimiter.
 * @return vector<string> The vector of delimited strings.
 */
vector<string> hashy:: split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

