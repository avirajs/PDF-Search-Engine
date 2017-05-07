/**
    CSE 2341 SearchEngine.cpp
    @brief The SearchEngine class uses the various class to create a PDF Search Engine.
    The class makes use of the DocumentParser, IndexHandler, and QueryEngie class to perform
    all of the various tasks of the Mantience mode and Query mode of the user interface.
    @author Aviraj Shina (owner)
    @author Patrick Yienger
    @version 1.0 05/07/17
*/

#include "searchengine.h"
#include "DocumentParser.h"
#include <algorithm>
#include <iomanip>
#include <stack>


/**
 * @brief SearchEngine::SearchEngine The search engine constructor.
 */
SearchEngine::SearchEngine() {
}

/**
 * @brief SearchEngine::chooseStructure Allows the user to choose between using a Hash table or AVLTree to create the inverted index file.
 * This also initalizes the IndexHandler, Documentparser, and QueryEngine objects to allow the Search Engine access to their functions.
 * It also updtes the tf/idf, inverted file index, page count, word count, and top fifty words.
 * @param type The user choice
 */
void SearchEngine::chooseStructure(char type) {
    ih= new IndexHandler(type);
    dp=new DocumentParser();
    dp->readInWordyMap();
    qe=new QueryEngine(ih,dp);
    this->readIndex();
    top50= ih->topFifty();
}

/**
 * @brief SearchEngine::addDocumentsToIndex Allows the user to choose between using a Hash table or AVLTree to create the inverted index file.
 * This also initalizes the IndexHandler, Documentparser, and QueryEngine objects to allow the Search Engine access to their functions.
 * It also updtes the tf/idf, inverted file index, page count, word count, and top fifty words.
 * @param type The user choice
 * @return bool The flag for a sucessful text extract.
 */
bool SearchEngine::addDocumentsToIndex(string docpath) {
    filePath = docpath;
    ih= new IndexHandler('H');
    dp = new DocumentParser(ih);
    flag = dp->extract(docpath);
    this->writeIndex();
    if (flag == false) {
        filePath = "";
    }
    this->writeFilePathToTXTFile();
    return flag;
}

/**
 * @brief SearchEngine::clear Allows the user to clear all of the stored data.
 * It cleares the inverted file index, the total page count, the total indexed word count,
 * the file paths, the bookmarks and the search history.
 */
void SearchEngine::clear() {
    this->clearIndex();
    this->clearTotalPages();
    this->clearWordTxt();
    this->clearFilePath();
    this->clearBookmarks();
    this->clearHistory();
}

/**
 * @brief SearchEngine::clearWordTxt This clears the total indexed word count .txt file.
 */
void SearchEngine::clearWordTxt() {
    dp = new DocumentParser();
    dp->clearWordTxt();
}

/**
 * @brief SearchEngine::display_search_results This searches the inverted file index for a query and displays the results.
 * @param word The query to search for.
 * @return vector<document> The vector containing the document objects from the query search.
 */
vector<document> SearchEngine::display_search_results(string word) {

    // cout<<"\nSearching: "<<word<<endl;
    const char separator    = ' ';
    vector<document> doc_results=qe->querySearch(word);
    vector<document> docsss;
    int cnt=0;
    int i =0;
    cout << endl;
    for(document doc:doc_results) {

        cout << right << setw(2) << ++i << ". Name: "<< left << setw(65) << setfill(separator) << doc.docname << " Count: " << left << setw(5) << setfill(separator) <<doc.count<<" Tf/idf: "<<doc.tdif<<endl;
        docsss.push_back(doc);
        if(cnt++==14) {
            break;
        }
    }
    return docsss;
}

/**
 * @brief SearchEngine::numWordsIndexed Returns the total indexed word count.
 * @return totalWordsIndexed
 */
int SearchEngine::numWordsIndexed() {
    return ih->totalWordsIndexed();
}

/**
 * @brief SearchEngine::topfifty Returns the top fifty most common words.
 * @return top50 The vector<document> containing the top fifty words and their count.
 */
vector<document> SearchEngine::topfifty() {
    return top50;
}

/**
 * @brief SearchEngine::getTotalPages Returns the total page count.
 * @return pages The total page count.
 */
int SearchEngine::getTotalPages() {
    int pages =0;
    ifstream fin;
    fin.open("total_pages.txt",fstream::app);
    while(!fin.eof()) {
        fin >> totalPages;
        pages += totalPages;
        totalPages =0;
    }
    return pages;
}

/**
 * @brief SearchEngine::readIndex This reads the index from the inverted index file and into the appropriate data structure.
 */
void SearchEngine::readIndex() {
    ih->readIndex();
}

/**
 * @brief SearchEngine::writeIndex This writes the index from the appropriate data structure and into the inverted file index.
 */
void SearchEngine::writeIndex() {
    ih->writeIndex();
}

/**
 * @brief SearchEngine::clearIndex This clears the inverted file index (.txt file).
 */
void SearchEngine::clearIndex() {
    ofstream fout("inverted_index.txt",ios::out);
    if(!fout) {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief SearchEngine::readTotalPages This outputs the total number of pages stored from the PDFs on the inverted index.
 * @return totalPages
 */
int SearchEngine::readTotalPages() {
    int pages =0;
    ifstream fin;
    fin.open("total_pages.txt",fstream::app);
    while(!fin.eof()) {
        fin >> totalPages;
        pages += totalPages;
        totalPages =0;
    }
    if (pages != 0) {
        cout << "The total page count is: " << pages << endl;
    }
    return pages;
}

/**
 * @brief SearchEngine::clearTotalPages This clears the total number of pages .txt file.
 */
void SearchEngine::clearTotalPages() {
    ofstream ouut("total_pages.txt",ios::out);
    if(!ouut) {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief SearchEngine::displayRawFile This dispalys the raw text of a requested PDF.
 * @param filePath The path to the requested PDF
 * @return bool The flag for a successful text extract.
 */
bool SearchEngine::displayRawFile(string filePath) {
    ih=new IndexHandler('H');
    dp=new DocumentParser(ih);
    flag = dp->rawTextExtract(filePath);
    return flag;
}

/**
 * @brief SearchEngine::displayTop50 This displays the top fifty words from the PDFs on the inverted index.
 */
void SearchEngine::displayTop50() {
    const char spacey = ' ';
    vector<document> vec = topfifty();
    for (int i =0; i < 50; i++) {
        int p = i+1;
        cout <<left<<setw(2) << p << ". " << setw(15) << setfill(spacey) << vec[i].docname << setw(10) << " Count: " << setw(5) << vec[i].count << endl;
    }
}

/**
 * @brief SearchEngine::writeFilePathToTXTFile This writes the file paths to a text file allowing the path to be stored.
 */
void SearchEngine::writeFilePathToTXTFile() {
    ofstream write;
    write.open("file_path.txt",fstream::app);
    // checks to see if file can open
    if(!write) {
        cout << "File FlightData can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }
    if (filePath != "") {
        write << filePath << endl;
    }
}

/**
 * @brief SearchEngine::readFilePathFromTXTFile This reads the file paths from the .txt file of file paths.
 * @return vector<string> The vector of the file paths.
 */
vector<string> SearchEngine::readFilePathFromTXTFile() {
    ifstream fin;
    vector<string> vecFile;
    fin.open("file_path.txt",fstream::app);
    while(!fin.eof()) {
        fin >> filePath;
        if (filePath != "") {
            vecFile.push_back(filePath);
        }
        filePath ="";
    }
    cout << "The table of file paths is: " << endl;
    for (int i =0; i < vecFile.size(); i++) {
        cout << i << ". " << vecFile[i] << endl;
    }
    return vecFile;
}

/**
 * @brief SearchEngine::clearFilePath This clears the file path .txt file.
 */
void SearchEngine::clearFilePath() {
    ofstream write("file_path.txt",ios::out);
    if(!write) {
        cout << "File FlightData can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

}

/**
 * @brief SearchEngine::readBookmarks This reads the bookmarks from the .txt file and adds them to the bookmark vector.
 */
void SearchEngine::readBookmarks() {
    ifstream fin("bookmarks.txt", ios::in);
    // checks to see if file can open
    if(!fin) {
        cout << "display book can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

    while(!(fin.eof())) {
        string line;
        getline(fin,line);
        if (line != "") {
            string book =line.substr(0,line.find("|"));
            string query = line.substr(line.find("|")+1);
            bookmarks.push_back(bookmark(book,query));
        }
    }
}

/**
 * @brief SearchEngine::addBookmark This adds bookmarks to the .txt file.
 * @param book The bookmark to be added.
 * @param query The query the bookmark was from.
 */
void SearchEngine::addBookmark(string book, string query) {
    ofstream ffout;
    ffout.open("bookmarks.txt",fstream::app);
    // checks to see if file can open
    if(!ffout) {
        cout << "book marks can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

    ffout << book << "|" << query << endl;
    bookmarks.push_back(bookmark(book,query));
}

/**
 * @brief SearchEngine::addToHistory This adds the query to the search history.
 * @param query The query to be added.
 */
void SearchEngine::addToHistory(string query) {
    const char separtor = ' ';
    ofstream ffout;
    ffout.open("history.txt",fstream::app);
    // checks to see if file can open
    if(!ffout) {
        cout << "histos can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    ffout<<left << setw(20) << setfill(separtor) << query <<" Year: " <<(now->tm_year + 1900) << " Month: " << (now->tm_mon + 1) << " Day: "<<  now->tm_mday<<endl;
}

/**
 * @brief SearchEngine::clearHistory This clears the history .txt file.
 */
void SearchEngine::clearHistory() {
    ofstream fout("history.txt",ios::out);
    if(!fout) {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief SearchEngine::displayHistory This displays the search history.
 */
void SearchEngine::displayHistory() {
    cout<<"Search History is:"<<endl;
    cout << endl;
    const char separtor = ' ';
    ifstream fin("history.txt", ios::in);
    // checks to see if file can open
    if(!fin) {
        cout << "display book can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }
    string line;
    int i =1;
    while(!(fin.eof())) {
        getline(fin,line);
        if (line != "") {
            cout<<"Query:"<< right << setw(2) << i << ". " << line<<endl;
        }
    }
}

/**
 * @brief SearchEngine::clearBookmarksThis clears the bookmarks .txt file.
 */
void SearchEngine::clearBookmarks() {
    ofstream fout("bookmarks.txt",ios::out);
    if(!fout) {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief SearchEngine::displayBookmarks This displays the bookmarks.
 * @return vector<bookmarks> The vector of bookmark objects that were displayed.
 */
vector<bookmark> SearchEngine::displayBookmarks() {
    const char seperator = ' ';
    int i=0;
    for(bookmark bm:bookmarks) {
        cout << right << setw(2) << setfill(seperator) << ++i <<". Bookmark: " << left << setw(60) << setfill(seperator) << bm.mark<< " Query: " << bm.query << endl;
        //if(i==10)
        //break;
    }
    return bookmarks;
}






























