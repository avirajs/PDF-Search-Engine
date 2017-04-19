

/***************************************************************************

 *   Copyright (C) 2006 by Dominik Seichter                                *

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



/*

 * Include the standard headers for cout to write

 * some output to the console.

 */

#include <string>
#include <iostream>
#include "textextractor.h"
#include <stack>
#include <vector>
#include <iomanip>

/*

 * Now include all podofo header files, to have access

 * to all functions of podofo and so that you do not have

 * to care about the order of includes.

 *

 * You should always use podofo.h and not try to include

 * the required headers on your own.

 */

#include "podofo/podofo.h"


/*

 * All podofo classes are member of the PoDoFo namespace.

 */

using namespace PoDoFo;
using namespace std;
/*
//got the method to extract strings from char* bb to work, need to add to it now
int main( int argc, char* argv[] )
{
    int x =0;
    int h =0;
    const char* p = "||||||||||||||||||||||||||||||";
    const char* c = "ofhhhhhhhhEndPop do";
    vector<String> a;
    const char* null = "\0";


    for (int i =0; i < strlen(c); i++)
    {
        char nn[30];

        char* n = nn;
        int value = (int)c[i];
        if(i != strlen(c)-1)
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
                String f = String(n);
                a.push_back(f);
                //reset n
                for (int u =0; u < 30; u++)
                {
                    n[u] = p[u];
                }
            }
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
                String f = String(n);
                a.push_back(f);
                //reset n
                for (int u =0; u < 30; u++)
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
                String f = String(n);
                a.push_back(f);
                //reset n
                for (int u =0; u < 30; u++)
                {
                    n[u] = p[u];
                }
            }

        }
        //get rest of char*
        if(i == strlen(c)-1)
        {
            for(int j =h; j < i+1; j++)
            {
                n[x] = c[j];
                x++;
            }
            n[x] = null[0];
            //convert n to string method
            String f = String(n);
            a.push_back(f);
        }
        x = 0;
    }
    int check =0;
}
*/
