/**
    CSE 2341 AVLTreeIndex.cpp
    @brief The AVLTreeindex is the custom implementation of the AVLTree.
    The code was based off of github implementation
    https://gist.github.com/harish-r/097688ac7f48bcbadfa5
    @author Aviraj Sinha (owner)
    @version 1.0 05/07/17
*/

#include "avltreeindex.h"
#include <regex.h>
using namespace std;

/**
 * @brief AVLTreeIndex::findIndex This finds the index of a specified word.
 * @param word_key The specified word.
 * @return vector<document> The vector of document that contains all off the PDF names and counts of the specified word.
 */
vector<document>*  AVLTreeIndex:: findIndex(string word_key) {

    index_node *temp=root;      //'head' is pointer to root node

    while(temp!=nullptr) {

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

/**
 * @brief AVLTreeIndex::addIndex This adds the index given a word and PDF name.
 * @param word The given word.
 * @param docname The given PDF name.
 */
void  AVLTreeIndex::addIndex(string& word, string& docname) {
    this->insert(word,docname);
}

/**
 * @brief AVLTreeIndex::display This displays the AVLTree
 */
void AVLTreeIndex::display() {
    inorder(root);
    cout << endl;
}

/**
 * @brief AVLTreeIndex::makeEmpty this clears the avl tree and is called by destructor
 *
 */
void AVLTreeIndex:: makeEmpty(index_node* t) {
    if(t == NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

/**
 * @brief AVLTreeIndex::insert This is used to insert from document parser and keeps count
 * @param x The the word to be added
 * @param docname The document name ot be added
 * @param t The recursively passing node
 * @return index_node The inserted node
 */
index_node* AVLTreeIndex:: insert(string x,string docname, index_node* t) {
    if(t == NULL) {
        t = new index_node;
        t->word_key = x;
        t->documents.push_back(document(docname));
        t->height = 0;
        t->left = t->right = NULL;
    } else if(x < t->word_key) {
        t->left = insert(x,docname, t->left);
        if(height(t->left) - height(t->right) == 2) {
            if(x < t->left->word_key)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    } else if(x > t->word_key) {
        t->right = insert(x,docname, t->right);
        if(height(t->right) - height(t->left) == 2) {
            if(x > t->right->word_key)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    } else {
        vector<document> *v= &t->documents;
        auto it = find_if(v->begin(), v->end(), [docname](const document& obj) {
            return obj.docname == docname;
        });
        if (it != v->end())
            (*it).count++;
        else//add document number
            v->push_back(document(docname));
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

/**
 * @brief AVLTreeIndex::singleRightRotate
 */
index_node* AVLTreeIndex:: singleRightRotate(index_node* &t) {
    index_node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

/**
 * @brief AVLTreeIndex::singleLeftRotate
 */
index_node* AVLTreeIndex:: singleLeftRotate(index_node* &t) {
    index_node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

/**
 * @brief AVLTreeIndex::doubleLeftRotate
 */
index_node*  AVLTreeIndex::doubleLeftRotate(index_node* &t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

/**
 * @brief AVLTreeIndex::doubleRightRotate
 */
index_node*  AVLTreeIndex::doubleRightRotate(index_node* &t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

/**
 * @brief AVLTreeIndex::findMin This finds the minimum value
 */
index_node* AVLTreeIndex:: findMin(index_node* t) {
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

/**
 * @brief AVLTreeIndex::findMax This finds the maximum value
 */
index_node*  AVLTreeIndex::findMax(index_node* t) {
    if(t == NULL)
        return NULL;
    else if(t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

/**
 * @brief AVLTreeIndex::remove This removes a node
 */
index_node*  AVLTreeIndex::remove(string x, index_node* t) {
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
    else if(t->left && t->right) {
        temp = findMin(t->right);
        t->word_key = temp->word_key;
        t->right = remove(t->word_key, t->right);
    }
    // With one or zero child
    else {
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
    if(height(t->left) - height(t->right) == 2) {
        // right right case
        if(height(t->left->left) - height(t->left->right) == 1)
            return singleLeftRotate(t);
        // right left case
        else
            return doubleLeftRotate(t);
    }
    // If right index_node is deleted, left case
    else if(height(t->right) - height(t->left) == 2) {
        // left left case
        if(height(t->right->right) - height(t->right->left) == 1)
            return singleRightRotate(t);
        // left right case
        else
            return doubleRightRotate(t);
    }
    return t;
}

/**
 * @brief AVLTreeIndex::height This finds the height
 */
int AVLTreeIndex:: height(index_node* t) {
    return (t == NULL ? -1 : t->height);
}

/**
 * @brief AVLTreeIndex::getBalance This balances the tree
 */
int  AVLTreeIndex::getBalance(index_node* t) {
    if(t == NULL)
        return 0;
    else
        return height(t->left) - height(t->right);
}

/**
 * @brief AVLTreeIndex::inorder This writes out the tree in-order
 */
void  AVLTreeIndex::inorder(index_node* t) {
    if(t == NULL)
        return;
    inorder(t->left);
    cout << t->word_key << ":";
    for(document doc: t->documents)
        cout<<doc.docname<<" "<<doc.count<<" ";

    inorder(t->right);
}

/**
 * @brief AVLTreeIndex::insert This inserts a document object into the AVLTree and updates the word count.
 * @param x The word to be inserted.
 * @param docname The PDF name to be inserted.
 * @param doc_count The count to be updated/set.
 */
index_node* AVLTreeIndex:: insert(string x,string docname, int doc_count, index_node* t) {
    if(t == NULL) {
        t = new index_node;
        t->word_key = x;
        document a(docname);
        a.count=doc_count;
        t->documents.push_back(a);
        t->height = 0;
        t->left = t->right = NULL;
    } else if(x < t->word_key) {
        t->left = insert(x,docname,doc_count,t->left);
        if(height(t->left) - height(t->right) == 2) {
            if(x < t->left->word_key)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    } else if(x > t->word_key) {
        t->right = insert(x,docname, doc_count,t->right);
        if(height(t->right) - height(t->left) == 2) {
            if(x > t->right->word_key)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    } else {
        document a(docname);
        a.count=doc_count;
        t->documents.push_back(a);
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

/**
 * @brief AVLTreeIndex::write_inorder This writes out ot the file in order
 */
void  AVLTreeIndex::write_inorder(index_node* t) {
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

/**
 * @brief AVLTreeIndex::AVLTreeIndex The AVLTree constructor.
 */
AVLTreeIndex::AVLTreeIndex() {
    root = NULL;
}

/**
 * @brief AVLTreeIndex::insert This inserts a word and PDF name into the AVL tree.
 * @param x The word to be inserted.
 * @param docname The PDF name to be inserted.
 */
void  AVLTreeIndex::insert(string x,string docname) {
    root = insert(x,docname, root);
}

/**
 * @brief AVLTreeIndex::insert This inserts the data from the inverted file index and into the hash table.
 * @param x The word to be inserted.
 * @param docname The PDF name to be inserted.
 * @param count The count to be inserted.
 */
void AVLTreeIndex::insert(string x,string docname, int count) {
    root = insert(x,docname,count,root);
}

/**
 * @brief AVLTreeIndex::remove This removes a word from the AVLTree
 */
void AVLTreeIndex:: remove(string x) {
    root = remove(x, root);
}

/**
 * @brief AVLTreeIndex::readIndex This reads the inverted file index and inserts the data into the AVLTree.
 */
void AVLTreeIndex::readIndex() {


    ifstream read("inverted_index.txt");
    if (!read) {
        cout << "file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    // cout << "File was opened" << endl;
    string line;

    string wordkey;
    string docname;
    int doccount=0;
    while(!(read.eof())) {
        getline(read,line);
        wordkey=line.substr(0,line.find("-"));

        vector<string> tokens=split(line.substr(line.find("-")+1),'|');

        int wordCorpusCount=0;
        for(int i=0; i<tokens.size(); i+=2) {
            docname=tokens[i];
            doccount=std::stoi(tokens[i+1]);
            // cout<<"word: "<<wordkey<<" doc name: "<<docname<<" count: "<<count<<endl;
            insert(wordkey,docname,doccount);
            wordCorpusCount+=doccount;
        }
        if(wordkey.size()>3)
            allwords.push_back(document(wordkey,wordCorpusCount));//not actually a document but a word and count
    }

}

/**
 * @brief AVLTreeIndex::totalWordsIndexed This returns the total words indexed.
 * @return int The total words indexed.
 */
int AVLTreeIndex::totalWordsIndexed() {
    allwords.size();
}

/**
 * @brief AVLTreeIndex::topwords This returns the top fifty words from the AVLTree.
 * @return vector<document> The vector of documents objects of the top fifty words and their counts.
 */
vector<document>AVLTreeIndex::topwords() {
    nth_element(allwords.begin(), allwords.begin()+49, allwords.end(), [ ]( const document& lhs, const document& rhs ) {
        return lhs.count > rhs.count;
    });

    vector<document>topfifty;
    for(int i=0; i<50; i++)
        topfifty.push_back(document(allwords[i].docname,allwords[i].count));

    sort( topfifty.begin( ), topfifty.end( ), [ ]( const document& lhs, const document& rhs ) {
        return lhs.count> rhs.count;
    });

    return topfifty;


}

/**
 * @brief AVLTreeIndex::writeIndex This writes the AVLTree to the inverted file index .txt file
 */
void AVLTreeIndex::writeIndex() {
    write_inorder((root));
}

/**
 * @brief AVLTreeIndex::split This splits the supplied string by a given delimiter.
 * @param s The string to be split.
 * @param delim The character to be used as the delimiter.
 * @return vector<string> The vector of delimited strings.
 */
vector<string> AVLTreeIndex:: split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}
