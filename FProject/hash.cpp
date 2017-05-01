#include "hash.h"
#include <math.h>


hashy::hashy()
{
    //sets elements of has table to default valuse
    for (int i =0; i < tableSize; i++)
    {
        //count docName word_key next
        HashTable[i] = new item;
        HashTable[i]->count = 0;
        HashTable[i]->docName = "empty";
        HashTable[i]->word_key = "empty";
    }
}

int hashy::Hashy(string key)
{
        const char* s = key.c_str();
        int hash = 0;
        while (*s)
        {
            hash = hash * 101  +  *s++;
        }
        return abs(hash%tableSize);
}

void hashy::addIndex(string &word, string &name)
{
    int index = Hashy(word);
    item* Ptr = HashTable[index];
    //If the index is empty
    if (HashTable[index]->word_key == "empty")
    {
        HashTable[index]->word_key = word;
        HashTable[index]->count++;
        HashTable[index]->docName = name;
        return;
    }
    //check to see if word already on index and has same doc name, increase count if so
    else
    {
        int i =0;
        int j = Ptr->vec.size();
        while (i != j)
        {
            string cword = Ptr->vec[i].word_key;
            string cdocName = Ptr->vec[i].docName;
            if (cword.compare(word) == 0)
            {
                if(cdocName.compare(name) == 0)
                {
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

int hashy::NumItemsInIndex(int index)
{
    int counts = 0;
    if (HashTable[index]->word_key == "empty")
    {
        return counts;
    }
    else
    {
        counts++;
        item* Ptr = HashTable[index];
        counts+= Ptr->vec.size();
    }
    return counts;
}

void hashy::display()
{
    int number;
    for (int i =0; i < tableSize; i++)
    {
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

void hashy::displayIndex(int index)
{
    item* Ptr = HashTable[index];
    if (Ptr->word_key == "empty")
    {
        cout << "The index is: " << index << endl;
        cout << "The index is empty" << endl;
    }
    else
    {
        cout << "The index is: " << index << endl;
        cout << "The number of words in the index is: " << NumItemsInIndex(index) << endl;
        int i =0;
        while(i < Ptr->vec.size())
        {
            cout << "------------------------" << endl;
            cout << "------------------------" << endl;
            cout << "The word is: " << Ptr->vec[i].word_key << endl;
            cout << "The doc name is: " << Ptr->vec[i].docName << endl;
            cout << "The count is: " << Ptr->vec[i].count << endl;
            i++;
        }
    }
}

vector<document>* hashy::findIndex(string word)
{
    int index = Hashy(word);
    vector<document>* data = new vector<document>;
    bool found = false;
    item* Ptr = HashTable[index];
    string cword = Ptr->word_key;
    if (cword.compare(word) == 0)
    {
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
    while(i < j)
    {
        string cword = Ptr->vec[i].word_key;
        if (cword.compare(word) == 0)
        {
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
    if (found)
    {
        //data = &list;
        return data;
    }
    else
    {
        data = nullptr;
        return data;
    }

}


