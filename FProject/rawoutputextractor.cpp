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
//I added the ConvertToVectorOfString method and updated the Init, ExtractText,
//and AddTextElement methods to use this new method

#include "rawoutputextractor.h"
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
rawOutputExtractor::rawOutputExtractor(IndexHandler*ih,indexextractor*ie )
{
    this->ih=ih;
    this->ie=ie;
}

rawOutputExtractor::rawOutputExtractor()
{

}

rawOutputExtractor::~rawOutputExtractor()
{
}

int rawOutputExtractor::getTotalPages()
{
    return totalPages;
}

void rawOutputExtractor::Init( const char* pszInput)
{
   // cout << "Start of init" << endl;
    if( !pszInput )
    {
       // cout << "!pszInput error" << endl;
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
       // cout << "!pszInput error" << endl;
    }
   // cout << "Before PdfMemDocument" << endl;
    PdfMemDocument document( pszInput );
   // cout << "After PdfMemDocument" << endl;
    int nCount = document.GetPageCount();
    //shows page count
    cout << endl;
    cout << "The raw output file for " << pszInput << " is: " << endl;
    cout << endl;
    totalPages += nCount;
    for( int i=0; i<nCount; i++ )
    {
        PdfPage* pPage = document.GetPage( i );

        this->ExtractText( &document, pPage );
    }


    //reset everything else
    num =0;
    lenPszData =0;
    k = 0;
    kk=0;
    v = 0;
    chV =0;
    chV2 =0;
    chV3 =0;
    chVEnd =0;
    tjToken = 0;
    fTJ =0;
    prevLenPszData =0;
    kHasBeenChangedAready =0;

    while (*bb)
    {
        bb++;
    }
    for (int i =0; i < 2000000; i++)
    {
         b[i] = conP[0];
    }
    cout << endl;
    cout << endl;
}

void rawOutputExtractor::ExtractText( PdfMemDocument* pDocument, PdfPage* pPage )
{
    const char*      pszToken = NULL;
    PdfVariant       var;
    EPdfContentsType eType;


    PdfContentsTokenizer tokenizer( pPage );

    double dCurPosX     = 0.0;
    double dCurPosY     = 0.0;
    bool   bTextBlock   = false;
    PdfFont* pCurFont   = NULL;

    std::stack<PdfVariant> stack;

    while( tokenizer.ReadNext( eType, pszToken, var ) )
    {
       // cout <<pszToken << endl;
        if( eType == ePdfContentsType_Keyword )
        {

            // support 'l' and 'm' tokens
            if( strcmp( pszToken, "l" ) == 0 || strcmp( pszToken, "m" ) == 0 )
            {
                dCurPosX = stack.top().GetReal();
                stack.pop();
                dCurPosY = stack.top().GetReal();
                stack.pop();
            }
            else if( strcmp( pszToken, "BT" ) == 0 )
            {

              //  cout << "The token is: " << pszToken << endl;
                bTextBlock   = true;
                // BT does not reset font
                // pCurFont     = NULL;
            }
            else if( strcmp( pszToken, "ET" ) == 0 )
            {
                if( strlen(bb) > 0)
                {
                    //convert bb to a string adding it to the vector, reset bb, reset k
                    ConvertToVectorOfString(bb);
                    while(*bb)
                    {
                    ++bb;
                    }
                     k=0;
                }
              //  cout << "The token is: " << pszToken << endl;
                if( !bTextBlock )
                    fprintf( stderr, "WARNING: Found ET without BT!\n" );
            }

            if( bTextBlock )
            {
                if( strcmp( pszToken, "Tf" ) == 0 )
                {
                    stack.pop();
                    PdfName fontName = stack.top().GetName();
                    PdfObject* pFont = pPage->GetFromResources( PdfName("Font"), fontName );
                    if( !pFont )
                    {
                        PODOFO_RAISE_ERROR_INFO( ePdfError_InvalidHandle, "Cannot create font!" );
                    }

                    pCurFont = pDocument->GetFont( pFont );
                    if( !pCurFont )
                    {
                       // fprintf( stderr, "WARNING: Unable to create font for object %i %i R\n",
                               //  pFont->Reference().ObjectNumber(),
                               //  pFont->Reference().GenerationNumber() );
                    }
                }
                else if( strcmp( pszToken, "Tj" ) == 0 || strcmp( pszToken, "'" ) == 0 )
                {

               //   cout << "The token is: " << pszToken << endl;
                    //set tjToken flag and reset prevLenPszData for every new Tj tag
                    prevLenPszData =0;
                    tjToken = 99;
                    //add text to bb array
                    AddTextElement( dCurPosX, dCurPosY, pCurFont, stack.top().GetString() );
                    stack.pop();
                    //Checks if bb array is greater than 2, if so gets ASCII values of second char and third char and last char
                    if(strlen(bb) > 3)
                    {
                        chV = (int)bb[1];
                        chV2 = (int)bb[2];
                        chV3 = (int)bb[3];
                        int end = strlen(bb);
                        chVEnd = (int)bb[end-1];

                    }
                    //Checks to see if the length of the char* data is not one or was two and a number
                    if (lenPszData != 1 && (lenPszData != 2 || ((v > 47) || (v < 58))))
                    {
                        //Checks to see if the second char is not a . or is (a . and not a space)
                        if (chV != 46 || (chV == 46 && (chV2 != 32 && chV3 > 64)))
                        {
                            //Checks to see if bb is not three or is (three and not uppercase)
                            if(strlen(bb) != 3 || (strlen(bb) == 3 && ((chV < 64) || (chV > 91))))
                            {
                                //if the end is a - change the index to write on bb to one less and contiue adding to bb
                                if(chVEnd == 45)
                                {
                                   k--;
                                }
                                else if (chP != 32 && spaceIsSeperate != 99)
                                {
                                    //convert bb to a string adding it to the vector, reset bb, reset k
                                    ConvertToVectorOfString(bb);
                                    while(*bb)
                                    {
                                    ++bb;
                                    }
                                     k=0;
                                }
                            }
                        }
                    }
                    //reset tjToken flag
                    tjToken = 0;

                }
                else if( strcmp( pszToken, "\"" ) == 0 )
                {

                 //   cout << "The token is: " << pszToken << endl;
                    AddTextElement( dCurPosX, dCurPosY, pCurFont, stack.top().GetString() );
                    stack.pop();
                    stack.pop(); // remove char spacing from stack
                    stack.pop(); // remove word spacing from stack
                }
                else if( strcmp( pszToken, "TJ" ) == 0 )
                {
                    //set flag TJ and reset prevLenPszData for every new TJ flag
                    fTJ = 99;
                    prevLenPszData = 0;
                //    cout << "The token is: " << pszToken << endl;
                    PdfArray array = stack.top().GetArray();
                    stack.pop();
                    for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
                    {
                        //Go through TJ tag extracting all of the text and adding it to the bb array
                        if( array[i].IsString() || array[i].IsHexString() )
                        {
                            AddTextElement( dCurPosX, dCurPosY, pCurFont, array[i].GetString() );
                        }
                        //endOfTJ++;
                        //set chVEnd flag to 0 MAY BE USELESS?
                        chVEnd =0;
                    }
                    //Checks if bb array is greater than 2, if so gets ASCII values of second char and third char and last char
                    if(strlen(bb) > 2)
                    {
                        chV = (int)bb[1];
                        chV2 = (int)bb[2];
                        int end = strlen(bb);
                        chVEnd = (int)bb[end-1];

                     }
                    //Checks to see if bb is not one, may need to switch to Tj check might be better
                    if (strlen(bb) != 1)
                    {
                           //if the last character is a -, decrease index k by one to write over it on next text call
                            if(chVEnd == 45)
                            {
                            k--;
                            }
                            else
                            {
                                //Convert to String bb and then reset bb and k
                                ConvertToVectorOfString(bb);
                                while(*bb)
                               {
                                ++bb;
                               }
                                k=0;
                            }
                      }
                    //reset flag TJ
                    fTJ =0;
                    }
            }
        }
        else if ( eType == ePdfContentsType_Variant )
        {
            stack.push( var );
        }
        else
        {
            // Impossible; type must be keyword or variant
            //THIS IS NON OCR ERROR
            //PODOFO_RAISE_ERROR( ePdfError_InternalLogic );
            stack.push(var);
        }
    }
}



void rawOutputExtractor::AddTextElement( double dCurPosX, double dCurPosY,
        PdfFont* pCurFont, const PdfString & rString )
{

    if( !pCurFont )
    {
       // cout << num << endl;
       // fprintf( stderr, "WARNING: Found text but do not have a current font: %s\n", rString.GetString() );
        return;
    }

    if( !pCurFont->GetEncoding() )
    {
      //  fprintf( stderr, "WARNING: Found text but do not have a current encoding: %s\n", rString.GetString() );
        return;
    }

    // For now just write to console
 //   cout << "Num is: " << num << endl;
    PdfString unicode = pCurFont->GetEncoding()->ConvertToUnicode( rString, pCurFont );
    //stores txt info in pszData
    const char* pszData = unicode.GetStringUtf8().c_str();
    //sets length of pszData
    lenPszData = strlen(pszData);
    num++;
    /*
    if (num == 12544)
    {
        int hahahah =9;
    }*/
    //sets v flag to be the ASCII value of the first element of pszData
    v = (int)pszData[0];
  //  cout << pszData << endl;
    //loops through pszData and adds each element to bb array based of off the starting index k
    //uses kk to store the next location for
    for (int i =0; pszData[i] != '\0'; i++)
    {
        bb[k+i] = pszData[i];
        kk=i+1;
    }
    //sets leng to current length of bb array
    int leng = strlen(bb);
    chP = pszData[0];

    if(chP == 32)
    {
        //no adding spaces tag
        spaceAtFront= 99;
    }
    if(lenPszData == 1 && chP ==32)
    {
        spaceIsSeperate =99;
    }
    //Checks to see if length of PszData  is more than one
    if (lenPszData != 1 && (spaceAtFront != 99 || tjToken == 99))
    {
        if(spaceIsSeperate != 99 )
        {
            //may need to change to index that you are adding in!!!!!!!!!!!!!!!!!!!!!1
            //stores first index of bb as an ASCII value, sets chVEnd to the ASCII value of the last txt extracted
            chV = (int)bb[0];
            //may need to add a begining of pszData...
            int end = strlen(bb);
            chVEnd = (int)bb[end-1];

            //if it is TJ and ends in a space, write next element where the space is
            if (fTJ == 99)
            {
                if ((lenPszData == 2 || lenPszData == 3) && chVEnd == 32)
                {
                    k += kk-1;
                    kHasBeenChangedAready = 99;

                }

            }
            //if the last text extracted is uppercase
            if(chVEnd > 64 && chVEnd < 91)
            {
                //add a space to the end bb
                bb[leng] = conP[0];
                //set position k to write over next after the space
                k += kk;
            }
            //if bb is larger than 2 and the ASCII value of the third to last character is lowercase and part of Tj command
            else if (strlen(bb) > 2 && ((int)bb[leng-3] > 96) && tjToken == 99)
            {
                if(chP ==32)
                {
                    //add space to end, have k write over the space
                    bb[leng] = conP[0];
                    k = leng;
                }
                else
                {
                //add a space to the end of bb
                bb[leng] = conP[0];
                //set position k to write over next after the space
                k += kk;
                }
            }
            //if pszData two or more and not any of the above conditions and doesnt already end in a space
            else if (chVEnd != 32 && chP!=32)
            {
                //add a space to end, add null terminator after space, increase k to reflect the changes
                bb[leng] = lll[0];
                bb[leng+1] = conP[0];
                k++;
                k+= kk;
            }
            else
            {
                bb[leng] = conP[0];
                if (kHasBeenChangedAready != 99)
                {
                     k += kk;
                }
                //reset kHasBeenChangedAlready
                kHasBeenChangedAready =0;
            }
        }

        if (spaceIsSeperate == 99)
        {
            bb[leng] = conP[0];
            k += kk;
        }
    }
    //if pszData was equal to one
    else
    {
        //set up to continue adding next letters
        bb[leng] = conP[0];
        k += kk;
    }

//clear out pszData
    while( *pszData ) {
        //printf("%02x", static_cast<unsigned char>(*pszData) );
        ++pszData;
    }

   // printf("(%.3f,%.3f) %s \n", dCurPosX, dCurPosY, unicode.GetStringUtf8().c_str() );
}


void rawOutputExtractor::ConvertToVectorOfString(char*c)
{
    int x =0;
    int h =0;
    const char* p = "||||||||||||||||||||||||||||||";
    const char* null = "\0";
    int l = strlen(c)-1;


    string docname=mm;
    docsName = mm;
    for (int i =0; i < l+1; i++)
    {
        char nn[200000];

        char* n = nn;
        int value = (int)c[i];

        if(i != l)
        {
            int valueA = (int)c[i+1];
            //if lower than upper convert to string from 0 to i
            if ((value > 96 && value < 123) && (valueA > 64 && valueA <91))
            {
                for(int j =h; j < i+1; j++)
                {
                    n[x] = c[j];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " ")
                {

                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }
            }
            //if it has a space
            if (value == 32)
            {
                for (int o = h; o < i; o++)
                {
                    n[x] = c[o];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " " && f != "")
                {
                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }

            }

            if (value == 46)
            {
                for (int o = h; o < i; o++)
                {
                    n[x] = c[o];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " " && f != "")
                {
                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }

            }

            if (value == 47)
            {
                for (int o = h; o < i; o++)
                {
                    n[x] = c[o];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " " && f != "")
                {
                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }

            }

            if (value == 44)
            {
                for (int o = h; o < i; o++)
                {
                    n[x] = c[o];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " " && f != "")
                {
                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }

            }

            if (value == 58)
            {
                for (int o = h; o < i; o++)
                {
                    n[x] = c[o];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " " && f != "")
                {
                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }

            }

            //if letter upper or lower and a number
            if (((value > 96 && value < 123) || (value > 64 && value <91)) && (valueA > 47 && valueA < 58))
            {
                for(int j =h; j < i+1; j++)
                {
                    n[x] = c[j];
                    x++;
                }
                n[x] = null[0];
                //set h to next element
                h = i+1;
                //convert n to string method
                string f = string(n);
                if (f != " ")
                {
                    cout << f << " ";
                }
                //reset n
                for (int u =0; u < 200; u++)
                {
                    n[u] = p[u];
                }
            }

        }
        //get rest of char*
        if(i == l)
        {
            for(int j =h; j < i+1; j++)
            {
                n[x] = c[j];
                x++;
            }
            n[x] = null[0];
            if(((int)n[0]> 64 && (int)n[0] < 91) || ((int)n[0]> 39 && (int)n[0] < 58))
            {
                if((((int)n[2]> 64 && (int)n[2] < 91) || ((int)n[2]> 47 && (int)n[2] < 58)))
                {
                    k=0;
                    return;
                }
                else if ((((int)n[3]> 64 && (int)n[3] < 91) || ((int)n[3]> 47 && (int)n[3] < 58)))
                {
                    k =0;
                    return;
                }
            }

            if (x > 1)
            {
                if (((int)n[0]> 64 && (int)n[0] < 91) || ((int)n[0]> 39 && (int)n[0] < 58))
                {
                    if((((int)n[1]> 64 && (int)n[1] < 91) || ((int)n[1]> 47 && (int)n[1] < 58)))
                    {
                        k=0;
                        return;
                    }
                }
                if ((int)n[0] < 65)
                {

                    k =0;
                    return;
                }
            }
            if ((int)n[0] == 91)
            {
                k=0;
                return;
            }

            //convert n to string method
            string f = string(n);
            if (f != " ")
            {
                cout << f << " ";
                //this->a.push_back(f);
            }
        }
        x = 0;
    }

}

string rawOutputExtractor::getDocName()
{
    return docsName;
}

int rawOutputExtractor::getWordCount()
{
    return wordCount;
}
