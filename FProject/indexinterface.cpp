#include <string>
#include <set>
using namespace std;
class IndexInterface
{
public:
  virtual set<string>* findIndex(string key) = 0; // Pure virtual function makes
  virtual void addIndex(string& word, string& doc) = 0;
  virtual void display()=0;
};
