#include "avltreeindex.h"
#include <regex.h>
using namespace std;
vector<document>*  AVLTreeIndex:: findIndex(string word_key)
{

    index_node *temp=root;      //'head' is pointer to root node

      while(temp!=nullptr)
      {

        if(word_key>temp->word_key)
            temp=temp->right;
        else if(word_key<temp->word_key)
            temp=temp->left;
        else if(temp->word_key==word_key)
            return &temp->documents;

      }
      if(temp==nullptr)
          return nullptr;
      else if(temp->word_key==word_key)
          return &(temp->documents);
}
void  AVLTreeIndex::addIndex(string& word, string& docname)
{
    this->insert(word,docname);
}
void AVLTreeIndex::display()
{
    inorder(root);
    cout << endl;
}

    void AVLTreeIndex:: makeEmpty(index_node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    index_node* AVLTreeIndex:: insert(string x,string docname, index_node* t)
    {
        if(t == NULL)
        {
            t = new index_node;
            t->word_key = x;
            t->documents.push_back(document(docname));
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->word_key)
        {
            t->left = insert(x,docname, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->word_key)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->word_key)
        {
            t->right = insert(x,docname, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->word_key)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        else
        {
            vector<document> *v= &t->documents;
            auto it = find_if(v->begin(), v->end(), [docname](const document& obj) {return obj.docname == docname;});
            if (it != v->end())
              (*it).count++;
            else//add document number
                v->push_back(document(docname));
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    index_node* AVLTreeIndex:: singleRightRotate(index_node* &t)
    {
        index_node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    index_node* AVLTreeIndex:: singleLeftRotate(index_node* &t)
    {
        index_node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    index_node*  AVLTreeIndex::doubleLeftRotate(index_node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    index_node*  AVLTreeIndex::doubleRightRotate(index_node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    index_node* AVLTreeIndex:: findMin(index_node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    index_node*  AVLTreeIndex::findMax(index_node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    index_node*  AVLTreeIndex::remove(string x, index_node* t)
    {
        index_node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

        // Searching for element
        else if(x < t->word_key)
            t->left = remove(x, t->left);
        else if(x > t->word_key)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->word_key = temp->word_key;
            t->right = remove(t->word_key, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If index_node is unbalanced
        // If left index_node is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right index_node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int AVLTreeIndex:: height(index_node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int  AVLTreeIndex::getBalance(index_node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void  AVLTreeIndex::inorder(index_node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->word_key << ":";
        for(document doc: t->documents)
            cout<<doc.docname<<" "<<doc.count<<" ";

        inorder(t->right);
    }

    //inserts the doccument to the word witht the correct doc count
    index_node* AVLTreeIndex:: insert(string x,string docname, int doc_count, index_node* t)
    {
        if(t == NULL)
        {
            t = new index_node;
            t->word_key = x;
            document a(docname);
                    a.count=doc_count;
            t->documents.push_back(a);
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->word_key)
        {
            t->left = insert(x,docname,doc_count ,t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->word_key)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->word_key)
        {
            t->right = insert(x,docname, doc_count,t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->word_key)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        else
        {
            document a(docname);
                    a.count=doc_count;
            t->documents.push_back(a);
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    void  AVLTreeIndex::write_inorder(index_node* t)
    {
        ofstream ifi;
        ifi.open("inverted_index.txt",fstream::app);


        if(t == NULL)
            return;
        write_inorder(t->left);


        ifi << t->word_key << "-";
        for(document doc: t->documents)
            ifi<<doc.docname<<"|"<<doc.count<<"|";
        ifi<<endl;


        write_inorder(t->right);
    }

     AVLTreeIndex::AVLTreeIndex()
    {
        root = NULL;
    }

    void  AVLTreeIndex::insert(string x,string docname)
    {
        root = insert(x,docname, root);
    }

    void AVLTreeIndex::insert(string x,string docname, int count)
    {
        root = insert(x,docname,count,root);
    }
    void AVLTreeIndex:: remove(string x)
    {
        root = remove(x, root);
    }



void AVLTreeIndex::readIndex()
{


    ifstream read("inverted_index.txt");
    if (!read)
    {
        cout << "file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "File was opened" << endl;
   string line;

   string wordkey;
   string docname;
   int count=0;
    while(!(read.eof()))
    {
        getline(read,line);
        wordkey=line.substr(0,line.find("-"));

        vector<string> tokens=split(line.substr(line.find("-")+1),'|');
        for(int i=0;i<tokens.size();i+=2)
        {
            docname=tokens[i];
            count=std::stoi(tokens[i+1]);
            // cout<<"word: "<<wordkey<<" doc name: "<<docname<<" count: "<<count<<endl;
            insert(wordkey,docname,count);
            topwords.push_back(document(docname,count));
        }
    }
}
void AVLTreeIndex::writeIndex()
{
    write_inorder((root));
}
std::vector<std::string> AVLTreeIndex:: split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
      // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
  }
