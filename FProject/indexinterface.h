#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>
#include <vector>
using namespace std;
struct document
{
    string docname;
    int count=1;
    double tdif=0;
    document(string name)
    {
        docname=name;
    }
    document(string name,string docname, int count)
    {
        this->count=count;
        docname=name;
    }
    string getName()
    {
        return docname;
    }
    void setName(string name)
    {
        docname= name;
    }
    void setCount (int num)
    {
        count =num;
    }
    int getCount()
    {
        return count;
    }
};
class IndexInterface
{
public:
  virtual vector<document>* findIndex(string key) = 0; // Pure virtual function makes
  virtual void addIndex(string& word, string& doc) = 0;
  virtual void display()=0;
  virtual void readIndex()=0;
  virtual void writeIndex()=0;

};
#endif // INDEXINTERFACE_H
