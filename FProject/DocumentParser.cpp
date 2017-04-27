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
    }

}

string DocumentParser::getStemmed(string& word)
{
    return ie->getStemmed(word);
}
bool DocumentParser::isStopWord(string& word)
{
    return ie->isStopWord(word);
}
