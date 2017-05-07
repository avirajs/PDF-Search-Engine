/**
    CSE 2341 QueryEngine.h
    @brief The QueryEngine uses the inverted file index and searches it
    given a properly formatted Boolean query. It also ranks the results
    using tf/idf statistics.
    @author Aviraj Shina (owner)
    @version 1.0 05/07/17
*/

#include "queryengine.h"

/**
 * @brief QueryEngine::QueryEngine The constructor for the query engine.
 * @param i The index handler object.
 * @param d The documpen parser object.
 */
QueryEngine::QueryEngine(IndexHandler *i,DocumentParser*d) {
    ih=i;
    dp=d;
}

/**
 * @brief QueryEngine::querySearch This searches the inverted index file for a given boolean query.
 * It calls the search method to earch for the words and returning the proper results based on
 * whether a union, intersection or difference was required.
 * @param query The query to search for.
 * @return vector<document> A vector of document objects containing the results of the search sorted by tf/idf values.
 */
vector<document> QueryEngine::querySearch(string query) {
    istringstream iss(query);
    vector<string> words{istream_iterator<string>{iss},
                         istream_iterator<string>{}};
    queue<string> searches;
    for(string word: words)
        searches.push(word);





    bool a=false;
    bool o=false;
    bool n=false;

    vector<document> currdocs;

    //simple search
    if(words.size()==1) {
        currdocs= search(words[0]);
        findTDIFs(currdocs);
        relevencySort(currdocs);

        return currdocs;
    }

    while(!searches.empty()) {

        if(searches.front()=="AND") {
            a=true;
            o, n=false;
            searches.pop();
        } else if(searches.front()=="OR") {
            o=true;
            a, n=false;
            searches.pop();
        } else if(searches.front()=="NOT") {
            n=true;
            o, a=false;
            searches.pop();
        } else if(a) {
            if(currdocs.empty()) {
                string temp=searches.front();
                searches.pop();
                currdocs=getIntersection(search(temp),search(searches.front()));
                searches.pop();
            } else {
                currdocs=getIntersection(currdocs,search(searches.front()));
                searches.pop();
            }
        } else if(o) {
            if(currdocs.empty()) {
                string temp=searches.front();
                searches.pop();
                currdocs=getUnion(search(temp),search(searches.front()));

                searches.pop();
            } else {
                currdocs=getUnion(currdocs,search(searches.front()));
                searches.pop();
            }
        } else if(n) {
            //should never be empty
            if(!currdocs.empty()) {
                currdocs=getDifference(currdocs,search(searches.front()));
                searches.pop();
            }
        } else { //NOT case with word a in front     a NOT b
            currdocs=search(searches.front());
            searches.pop();
        }
    }
    relevencySort(currdocs);




    return currdocs;

}

/**
 * @brief QueryEngine::search This searches the inverted index file for a word, returning the results.
 * @param word The word to search for.
 * @return vector<document> A vector of document objects containing the results of the search.
 */
vector<document> QueryEngine::search(string word) {
    vector<document>*found;
    // cout<<"Document titles containing "<<word<<":"<<endl;
    if(dp->isStopWord(word)) {
        found=new vector<document>();
        cout<<word<<" is a stop word"<<endl;
        return *found;
    } else {
        string stem=(dp->getStemmed(word));
        found=ih->getDocs(stem);
        if(found!=nullptr) {
            return *found;
        } else {
            found=new vector<document>();
            cout<<"No documents found"<<endl;
            return *found;
        }
    }

    cout<<endl;

}

/**
 * @brief QueryEngine::getIntersection This returns the intersection of two queries.
 * @param l The vector<document> of the first query.
 * @param r The vector<document> of the secnd query.
 * @return vector<document> The intersection of the first and second query.
 */
vector<document>  QueryEngine::getIntersection(vector<document> l,vector<document> r) {
    findTDIFs(l);
    findTDIFs(r);
    vector<document> doc_intersection;
    for(document doc:r) {
        //searches for rhs words in left vector
        auto it = find_if(l.begin(), l.end(), [&doc]( document& obj) {
            return obj.getName() == doc.docname;
        });
        if (it != l.end()) {
            doc.count+=(*it).count;
            doc.tdif+=(*it).tdif;
            doc_intersection.push_back(doc);
        }
    }
    return doc_intersection;

}

/**
 * @brief QueryEngine::getUnion This returns the union of two queries.
 * @param l The vector<document> of the first query.
 * @param r The vector<document> of the secnd query.
 * @return vector<document> The union of the first and second query.
 */
vector<document> QueryEngine::getUnion(vector<document> l,vector<document> r) {

    //searches for rhs words in left vector
    findTDIFs(l);
    findTDIFs(r);
    for(document doc:r) {
        auto it = find_if(l.begin(), l.end(), [&doc]( document& obj) {
            return obj.getName() == doc.docname;
        });
        if (it == l.end()) {
            l.push_back(doc);
        }
        if (it != l.end()) {
            (*it).count+=doc.count;
            (*it).tdif+=doc.tdif;
        }
    }
    return l;
}

/**
 * @brief QueryEngine::getDifference This returns the difference of two queries.
 * @param l The vector<document> of the first query.
 * @param r The vector<document> of the secnd query.
 * @return vector<document> The difference of the first and second query.
 */
vector<document> QueryEngine::getDifference(vector<document> r,vector<document> l) {
    findTDIFs(l);
    findTDIFs(r);
    vector<document> doc_diff;
    for(document doc:r) {
        //searches for rhs words in left vector
        auto it = find_if(l.begin(), l.end(), [&doc]( document& obj) {
            return obj.getName() == doc.docname;
        });
        if (it == l.end()) {
            doc_diff.push_back(doc);
        }
    }
    return doc_diff;
}

/**
 * @brief QueryEngine::findTDIFs This caculates the tf/idf values of the query results.
 * @param currdocs The vector<document> to caculate the tf/idf for.
 */
void QueryEngine::findTDIFs(vector<document>& currdocs) {
    int corpus_sum=0;
    for (unsigned j=0; j<currdocs.size(); j++) {
        corpus_sum+= currdocs.at(j).count;
    }
    for(document &doc: currdocs) {
        int p = dp->wordy.size();
        int pp = currdocs.size();
        int ppp = doc.count;
        int pppp = dp->wordy[doc.docname];
        doc.tdif=log(1.*dp->wordy.size()/currdocs.size())*(1.*doc.count/dp->wordy[doc.docname]);
    }

}

/**
 * @brief QueryEngine::relevencySort This sorts the vector<document> by tf/idf value.
 * @param currdocs The vector<document> to be sorted.
 */
void QueryEngine::relevencySort(vector<document>& currdocs) {

    sort( currdocs.begin( ), currdocs.end( ), [ ]( const document& lhs, const document& rhs ) {
        return lhs.tdif> rhs.tdif;
    });

}
