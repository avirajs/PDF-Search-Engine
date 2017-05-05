#include "indexextractor.h"
#include "textextractor.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "DocumentParser.h"
//#include <config.h>



DocumentParser::DocumentParser(IndexHandler* i)
{
ih=i;
ie= new indexextractor("stopwords.txt");
}
DocumentParser::DocumentParser()
{
ie= new indexextractor("stopwords.txt");
}
void DocumentParser::extract(string fileStream)
{



    //pdir = opendir("/home/coder/Documents/Corpus01/sampleCorpus");
    pdir = opendir(fileStream.c_str());
    struct dirent *pent = nullptr;
    if (pdir == nullptr)
    {
        cout << "\n Error! pdir coud not be initialised correctly" << endl;
        exit (3);
    }
    while (pent = readdir(pdir))
    {
        cDot =0;
        cP =0;
        if (pent == nullptr)
        {
            cout << "\n Error! pent coud not be initialised correctly" << endl;
            exit (3);
        }
        nn = pent->d_name;
        int slen = strlen(nn);
        if (slen > 4)
        {
            cDot = (int)nn[slen-4];
            cP = (int)nn[slen-3];
        }
        if (cDot == 46 && cP == 112)
        {
            string b(nn);
            k.push_back(b);
        }
        //reset nn
        while(*nn)
        {
            ++nn;
        }
    }
    closedir(pdir);


    for (int i = 0; i < k.size(); i++)
    {
        if (i == 5)
        {
            int helpme =0;
        }
      TextExtractor extractor(ih,ie);
      string names = fileStream;
      string ne = names + k[i];
      const char * mm = ne.c_str();
      try {
         extractor.Init(mm,k[i]);
         m.push_back(extractor);
      } catch( PdfError & e ) {
          fprintf( stderr, "Error: An error %i ocurred during processing the pdf file.\n", e.GetError() );
          e.PrintErrorMsg();
      }
       totalPages += extractor.getTotalPages();
       docName = k[i];
       wordCount = extractor.getWordCount();
       wordy[docName]=wordCount;
    }
    int k =0;
    ofstream write;
    write.open("total_pages.txt",fstream::app);
    // checks to see if file can open
      if(!write)
      {
          cout << "File FlightData can't be opened. Exiting Program." << endl;
          exit (EXIT_FAILURE);
      }
    write << totalPages << endl;
    for (auto elem : wordy)
    {
        //cout << elem.first << " " << elem.second << endl;
        ofstream ffout;
        ffout.open("pdf_and_wordCount.txt",fstream::app);
        // checks to see if file can open
          if(!ffout)
          {
              cout << "File FlightData can't be opened. Exiting Program." << endl;
              exit (EXIT_FAILURE);
          }
        ffout << elem.first << "|" << elem.second << endl;
    }
}


int DocumentParser::getTotalPages()
{
    return totalPages;
}

string DocumentParser::getStemmed(string& word)
{
    return ie->getStemmed(word);
}
bool DocumentParser::isStopWord(string& word)
{
    return ie->isStopWord(word);
}
int DocumentParser::numOfDocs()
{
    return wordy.size();
}
void DocumentParser::readInWordyMap()
{
    ifstream fin("pdf_and_wordCount.txt", ios::in);
        // checks to see if file can open
        if(!fin)
        {
            cout << "File FlightData can't be opened. Exiting Program." << endl;
            exit (EXIT_FAILURE);
        }
        while(!(fin.eof()))
        {
            string line;
            getline(fin,line);
            if (line != "")
            {
                string doc;
                doc =line.substr(0,line.find("|"));
                string words = line.substr(line.find("|")+1);
                int word;
                word = std::stoi(words);
                wordy[doc]=word;
            }
        }
        int helpme =0;
}
void DocumentParser::clearWordTxt()
{
    ofstream fout("pdf_and_wordCount.txt", ios::out);
    fout.close();
}
