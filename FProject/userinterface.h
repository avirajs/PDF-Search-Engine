/**
    CSE 2341 UserInterface.h
    @brief The UserInterface is a command line menu driven class that makes use of the SearchEngine.
    It allows the user to enter into two modes, Maintainence and Query, allows the user many options
    including adding a new pdf to the inverted index, clearing the index, searching the PDF, outputting total pages,
    outputting total words indexed, outputting the top fifty words, outputting the corpus paths, storing and clearing
    the search history, storing and clearing bookmarks and outputting the raw text from a selected pdf.
    @author Patrick Yienger (owner)
    @version 1.0 05/07/17
*/

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "searchengine.h"
#include "DocumentParser.h"

/**
 * @brief The userinterface class
 */
class userinterface
{
public:

    userinterface();
    /**
     * @brief use method runs the user interface.
     * It
     */
    void use();
private:string filePath;
    string query;
    string path;
    string temp;
    string other;
    string book;
    bool boo = false;
    bool check = false;
    bool historyFlag = false;
    bool bookmarkFlag = false;
    char d='1';
    char r;
    char s;
    char t;
    int tt;
    char k;
    char g;
    char p;
    char y;
    char q;
    char b;
    int res;
    SearchEngine se;
    int num =0;


};

#endif // USERINTERFACE_H
