#include "searchengine.h"
#include "DocumentParser.h"
#include <algorithm>
#include <iomanip>
#include <stack>

//read from inverted index without parsing
void SearchEngine::chooseStructure(char type)
{
   ih= new IndexHandler(type);
   dp=new DocumentParser();
   dp->readInWordyMap();
   qe=new QueryEngine(ih,dp);
   this->readIndex();
   top50= ih->topFifty();
}

SearchEngine::SearchEngine()
{
}

bool SearchEngine::addDocumentsToIndex(string docpath)
{
    filePath = docpath;
    //create a whole index handler to allow the counts to be stored too
    ih= new IndexHandler('H');
    dp = new DocumentParser(ih);
    flag = dp->extract(docpath);
    this->writeIndex();
    if (flag == false)
    {
        filePath = "";
    }
    this->writeFilePathToTXTFile();
    return flag;

    //not clearing
}

void SearchEngine::clear()
{
    this->clearIndex();
    this->clearTotalPages();
    this->clearWordTxt();\
    this->clearFilePath();
    this->clearBookmarks();
    this->clearHistory();
}

void SearchEngine::clearWordTxt()
{
    dp = new DocumentParser();
    dp->clearWordTxt();
}

vector<document> SearchEngine::display_search_results(string word)
{

   // cout<<"\nSearching: "<<word<<endl;
    const char separator    = ' ';
    vector<document> doc_results=qe->querySearch(word);
    vector<document> docsss;
    int cnt=0;
    int i =0;
    cout << endl;
    for(document doc:doc_results)
    {

        cout << right << setw(2) << ++i << ". Name: "<< left << setw(65) << setfill(separator) << doc.docname << " Count: " << left << setw(5) << setfill(separator) <<doc.count<<" Tdif: "<<doc.tdif<<endl;
        docsss.push_back(doc);
        if(cnt++==14)
        {
            break;
        }
    }
    return docsss;
}

int SearchEngine::numWordsIndexed()
{
 return ih->totalWordsIndexed();
}

vector<document> SearchEngine::topfifty()
{
 return top50;
}

int SearchEngine::getTotalPages()
{
    int pages =0;
    ifstream fin;
    fin.open("total_pages.txt",fstream::app);
    while(!fin.eof())
    {
        fin >> totalPages;
        pages += totalPages;
        totalPages =0;
    }
    return pages;
}

void SearchEngine::readIndex()
{
     ih->readIndex();
}

void SearchEngine::writeIndex()
{
 ih->writeIndex();
}

void SearchEngine::clearIndex()
{
    ofstream fout("inverted_index.txt",ios::out);
    if(!fout)
    {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}

int SearchEngine::readTotalPages()
{
    int pages =0;
    ifstream fin;
    fin.open("total_pages.txt",fstream::app);
    while(!fin.eof())
    {
        fin >> totalPages;
        pages += totalPages;
        totalPages =0;
    }
    if (pages != 0)
    {
        cout << "The total page count is: " << pages << endl;
    }
    return pages;
}

void SearchEngine::clearTotalPages()
{
 ofstream ouut("total_pages.txt",ios::out);
 if(!ouut)
 {
     cout<<"clear file cant be opened"<<endl;
     exit(EXIT_FAILURE);
 }
}

bool SearchEngine::displayRawFile(string filePath)
{
    ih=new IndexHandler('H');
    dp=new DocumentParser(ih);
    flag = dp->rawTextExtract(filePath);
    return flag;
}

void SearchEngine::displayTop50()
{
    const char spacey = ' ';
    vector<document> vec = topfifty();
    for (int i =0; i < 50; i++)
    {
        int p = i+1;
        cout <<left<<setw(2) << p << ". " << setw(15) << setfill(spacey) << vec[i].docname << setw(10) << " Count: " << setw(5) << vec[i].count << endl;
    }
}

void SearchEngine::writeFilePathToTXTFile()
{
    ofstream write;
    write.open("file_path.txt",fstream::app);
    // checks to see if file can open
    if(!write)
    {
        cout << "File FlightData can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }
    if (filePath != "")
    {
        write << filePath << endl;
    }
}

vector<string> SearchEngine::readFilePathFromTXTFile()
{
    ifstream fin;
    vector<string> vecFile;
    fin.open("file_path.txt",fstream::app);
    while(!fin.eof())
    {
        fin >> filePath;
        if (filePath != "")
        {
            vecFile.push_back(filePath);
        }
        filePath ="";
    }
    cout << "The table of file paths is: " << endl;
    for (int i =0; i < vecFile.size(); i++)
    {
         cout << i << ". " << vecFile[i] << endl;
    }
    return vecFile;
}

void SearchEngine::clearFilePath()
{
    ofstream write("file_path.txt",ios::out);
    if(!write)
    {
        cout << "File FlightData can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

}

void SearchEngine::readBookmarks()
{
    ifstream fin("bookmarks.txt", ios::in);
     // checks to see if file can open
     if(!fin)
     {
          cout << "display book can't be opened. Exiting Program." << endl;
          exit (EXIT_FAILURE);
     }

     while(!(fin.eof()))
     {
      string line;
      getline(fin,line);
      if (line != "")
      {
            string book =line.substr(0,line.find("|"));
            string query = line.substr(line.find("|")+1);
            bookmarks.push_back(bookmark(book,query));
       }
    }
}

void SearchEngine::addBookmark(string book, string query)
{
    ofstream ffout;
    ffout.open("bookmarks.txt",fstream::app);
    // checks to see if file can open
    if(!ffout)
    {
        cout << "book marks can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }

    ffout << book << "|" << query << endl;
    bookmarks.push_back(bookmark(book,query));
}

void SearchEngine::addToHistory(string query)
{
    const char separtor = ' ';
    ofstream ffout;
    ffout.open("history.txt",fstream::app);
    // checks to see if file can open
    if(!ffout)
    {
         cout << "histos can't be opened. Exiting Program." << endl;
         exit (EXIT_FAILURE);
    }

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    ffout<<left << setw(20) << setfill(separtor) << query <<" Year: " <<(now->tm_year + 1900) << " Month: " << (now->tm_mon + 1) << " Day: "<<  now->tm_mday<<endl;
}

void SearchEngine::clearHistory()
{
    ofstream fout("history.txt",ios::out);
        if(!fout)
        {
            cout<<"clear file cant be opened"<<endl;
            exit(EXIT_FAILURE);
    }
}

void SearchEngine::displayHistory()
{
    cout<<"Search History is:"<<endl;
    cout << endl;
    const char separtor = ' ';
    ifstream fin("history.txt", ios::in);
    // checks to see if file can open
    if(!fin)
    {
        cout << "display book can't be opened. Exiting Program." << endl;
        exit (EXIT_FAILURE);
    }
    string line;
    int i =1;
    while(!(fin.eof()))
    {
       getline(fin,line);
       if (line != "")
       {
            cout<<"Query:"<< right << setw(2) << i << ". " << line<<endl;
       }
    }
}

void SearchEngine::clearBookmarks()
{
    ofstream fout("bookmarks.txt",ios::out);
    if(!fout)
    {
        cout<<"clear file cant be opened"<<endl;
        exit(EXIT_FAILURE);
    }
}

vector<bookmark> SearchEngine::displayBookmarks()
{
    const char seperator = ' ';
    int i=0;
    for(bookmark bm:bookmarks)
    {
        cout << right << setw(2) << setfill(seperator) << ++i <<". Bookmark: " << left << setw(60) << setfill(seperator) << bm.mark<< " Query: " << bm.query << endl;
        //if(i==10)
        //break;
     }
    return bookmarks;
}






























