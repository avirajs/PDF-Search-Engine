/**
    CSE 2341 QueryEngine.h
    @brief The QueryEngine uses the inverted file index and searches it
    given a properly formatted Boolean query. It also ranks the results
    using tf/idf statistics.
    @author Aviraj Shina (owner)
    @version 1.0 05/07/17
*/
#ifndef QUERYENGINE_H
#define QUERYENGINE_H
#include <vector>
#include <math.h>
#include "indexhandler.h"
#include "DocumentParser.h"

/**
 * @brief The QueryEngine class
 */
class QueryEngine {
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
