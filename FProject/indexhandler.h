
#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include "indexhandler.h"
#include "avltreeindex.h"
using namespace std;

class IndexHandler
{
private:
    IndexInterface *index;
    //index interface pointer
public:
    IndexHandler();//add argument to decide which data structure to create but for now avl tree
    void addIndex(string,string);
    set<string>* getDocs(string);
    void displayIndices();
};

#endif // INDEXHANDLER_H
