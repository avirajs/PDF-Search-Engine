#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "searchengine.h"
#include "DocumentParser.h"

class userinterface
{
public:
    /**
     * @brief userinterface the object constructor
     */
    userinterface();
    /**
     * @brief the use method runs the user interface
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
