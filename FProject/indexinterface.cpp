#include <string>
#include <set>
using namespace std;
class IndexInterface
{
public:
  virtual set<int>* findIndex(string key) = 0; // Pure virtual function makes
  virtual void addIndex(string word, int doc) = 0;
  virtual void display()=0;
};
