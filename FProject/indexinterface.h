/**
    CSE 2341 IndexInterface.h
    @brief The IndexInterface is the common shared interface used by
    the custom AVLTree and HashTable
    @author Aviraj Shina (owner)
    @author Patrick Yienger
    @version 1.0 05/07/17
*/
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>
#include <vector>
using namespace std;

/**
 * @brief The document struct This struct conatins a string used as the word or the PDF name, and an int used as the count, and a double for the tf/idf.
 * This struct is used in many different ways depending on the function it is used in.
 */
struct document {
    string docname;
    int count=1;
    double tdif=0;
    document(string name) {
        docname=name;
    }
    document(string name,int count) {
        this->count=count;
        docname=name;
    }
    string getName() {
        return docname;
    }
    void setName(string name) {
        docname= name;
    }
    void setCount (int num) {
        count =num;
    }
    int getCount() {
        return count;
    }
};

/**
 * @brief The IndexInterface class
 */
class IndexInterface {
public:
    virtual vector<document>* findIndex(string key) = 0; // Pure virtual function makes
    virtual void addIndex(string& word, string& doc) = 0;
    virtual void display()=0;
    virtual void readIndex()=0;
    virtual void writeIndex()=0;
    virtual vector<document>topwords()=0;
    virtual int totalWordsIndexed()=0;

};
#endif // INDEXINTERFACE_H
