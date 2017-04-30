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
        HashTable[i]->next = nullptr;
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
    bool alreadyOn = false;
    item* alreadyOnPtr;
    item* Ptr = HashTable[index];
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
        while (Ptr != nullptr)
        {
            string cword = Ptr->word_key;
            string cdocName = Ptr->docName;
            if (cword.compare(word) == 0)
            {
                if(cdocName.compare(name) == 0)
                {
                    //increase the count for repeat words in the same document
                    alreadyOn = true;
                    alreadyOnPtr = Ptr;
                }
            }
            Ptr = Ptr->next;
        }
    }
    //if already on, increase the count
    if (alreadyOn)
    {
        alreadyOnPtr->count++;
    }
    else
    {
        Ptr = HashTable[index];
        while (Ptr->next != nullptr)
        {
            Ptr = Ptr->next;
        }
        item* n = new item;
        n->count++;
        n->docName = name;
        n->word_key = word;
        n->next = nullptr;
        Ptr->next = n;
    }
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
        item* Ptr = HashTable[index]->next;
        while(Ptr != nullptr)
        {
            counts++;
            Ptr = Ptr->next;
        }
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
        while(Ptr != nullptr)
        {
            cout << "------------------------" << endl;
            cout << "------------------------" << endl;
            cout << "The word is: " << Ptr->word_key << endl;
            cout << "The doc name is: " << Ptr->docName << endl;
            cout << "The count is: " << Ptr->count << endl;
            Ptr = Ptr->next;
        }
    }
}

vector<document>* hashy::findIndex(string word)
{
    int index = Hashy(word);
    vector<document>* data;
    vector<document> list;
    bool found = false;
    item* Ptr = HashTable[index];
    while(Ptr != nullptr)
    {
        string cword = Ptr->word_key;
        if (cword.compare(word) == 0)
        {
             string d = "empty";
             document* docs = new document(d);
             int num = Ptr->count;
             string name = Ptr->docName;
             docs->setCount(num);
             docs->setName(name);
             list.push_back(*docs);
             found = true;
        }
        Ptr = Ptr->next;
    }
    if (found)
    {
        return &list;
    }
    else
    {
        data = nullptr;
        return data;
    }

}































