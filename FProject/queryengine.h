#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include "indexinterface.cpp"
class QueryEngine
{
public:
    QueryEngine();
    vector<document> querySearch(string);

private:
    void findTDIFs(vector<document>& currdocs);
    vector<document> getIntersection(vector<document>,vector<document>);
    vector<document> getUnion(vector<document>,vector<document>);
    vector<document> getDifference(vector<document>,vector<document>);
    vector<document> search(string);
    void relevencySort(vector<document>& );
};

#endif // QUERYENGINE_H
