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
        int count=1;
        docname=name;
    }
    string getName()
    {
        return docname;
    }
};
class IndexInterface
{
public:
  virtual vector<document>* findIndex(string key) = 0; // Pure virtual function makes
  virtual void addIndex(string& word, string& doc) = 0;
  virtual void display()=0;
};
