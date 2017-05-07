/***************************************************************************
 *   Copyright (C) 2008 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/**
    CSE 2341 TextExtractor.h
    @brief The TextExtractor uses Podofo to extract the raw text from a pdf, convert it itno usable strings and
    pass those stings to the IndexExtractor and IndexInterface for stop word removal and stemming.
    The code was based off of the stack based text extractor provided in the podofo tools and documented above.
    Its original code was modified to better output/combine the various raw text into words and strings.
    The method of ConvertToVectorOfString(char c) was added, and the rest were modified for use in the
    PDF Search engine.
    @author Patrick Yienger (owner)
    @version 1.0 05/07/17
*/
#ifndef _TEXT_EXTRACTOR_H_
#define _TEXT_EXTRACTOR_H_

#include "podofo/podofo.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace PoDoFo;
using namespace std;

#ifndef MAX_PATH
#define MAX_PATH 512
#endif // MAX_PATH

#include "indexhandler.h"
#include "indexextractor.h"
#include "map"

/**
 * @brief The TextExtractor class
 */
class TextExtractor {
public:
    IndexHandler* ih;
    indexextractor* ie;
    string mm;
    vector<string> a;
    TextExtractor(IndexHandler*,indexextractor*);
    virtual ~TextExtractor();
    int getTotalPages();
    int wordCount =0;
    string docsName;
    string getDocName();
    int getWordCount();
    void Init( const char* pszInput, string docName);

private:
    int totalPages;
    int chP = 0;
    int num =0;
    int lenPszData =0;
    const char* p = "|";
    const char* conP = "\0";
    const char* lll = " ";
    int k = 0;
    int kk=0;
    char b[2000000];
    char* bb = b;
    int v = 0;
    int chV =0;
    int chV2 =0;
    int chV3 =0;
    int chVEnd =0;
    int tjToken = 0;
    int fTJ =0;
    int prevLenPszData =0;
    int kHasBeenChangedAready =0;
    int spaceAtFront =0;
    int spaceIsSeperate =0;

    void ConvertToVectorOfString(char* c);


    void ExtractText( PdfMemDocument* pDocument, PdfPage* pPage );


    void AddTextElement( double dCurPosX, double dCurPosY,
                         PdfFont* pCurFont, const PdfString & rString );
};

#endif // _TEXT_EXTRACTOR_H_
