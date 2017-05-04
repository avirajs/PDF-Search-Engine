#ifndef QUERYENGINE_H
#define QUERYENGINE_H
#include <vector>
#include <math.h>
#include "indexhandler.h"
#include "DocumentParser.h"

class QueryEngine
{
private:
    IndexHandler *ih;
    DocumentParser*dp;
public:
    int fileSize=0;
    QueryEngine(IndexHandler *,DocumentParser*);

    vector<document> querySearch(string query);
    vector<document> search(string word);
    vector<document>  getIntersection(vector<document> l,vector<document> r);
    vector<document> getUnion(vector<document> l,vector<document> r);
    vector<document> getDifference(vector<document> r,vector<document> l);
    void findTDIFs(vector<document>& currdocs);
    void relevencySort(vector<document>& currdocs);


};

#endif // QUERYENGINE_H
