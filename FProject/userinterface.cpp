#include "userinterface.h"

userinterface::userinterface()
{

}
void userinterface::use()
{
    cout<<"Welcome to the Pdf Search Engine." << endl;
    while(d!='0') {
        cout << endl;
        cout<<"Press 'M' to enter maintainence mode or 'Q' for querying or '0' to exit."<< endl;
        cin>>d;
        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
        if(d=='M') {
            cout << endl;
            cout<<"Enter 'A' to add a corpus and 'C' to clear the index."<<endl;
            cin>>r;
            cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
            if (r == 'A') {
                while(r =='A') {
                    cout << endl;
                    cout<<"Enter the corpus path:"<<endl;
                    getline(std::cin,filePath);
                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                    check = se.addDocumentsToIndex(filePath);
                    if (check == true) {
                        cout << "Would you like to enter in another document path? Enter 'Y' for yes, 'N' for no." << endl;
                        cin >> p;
                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                        if (p != 'Y') {
                            r = '?';
                        }
                    } else {
                        cout << "The file path was invalid. Enter 'T' to try again and enter 'E' to exit." << endl;
                        cin >> p;
                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                        if (p != 'T') {
                            r = '?';
                        }
                        cin.clear();
                    }
                }
            } else if(r=='C') {
                se.clear();
                cout << endl;
                cout<<"Cleared"<<endl;
            }
        } else if (d=='Q') {
            int number = se.getTotalPages();
            if (number == 0) {
                cout << endl;
                cout << "There is currently no inverted index file. Please add a document path in Maintainence mode to continue." << endl;
            } else {
                cout << endl;
                cout<<"Press 'H' to use Hashtable Query and 'A' for AVL Tree Query and press 'B' to see the Basic Statistics Menu."<<endl;
                cin >> s;
                cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                if (s == 'B') {
                    cout << endl;
                    se.chooseStructure('H');
                }
                while (s == 'B') {
                    cout << "Enter in 'P' for the total number of pages indexed." << endl;
                    cout << "Enter in 'W' for the total number of words indexed." << endl;
                    cout << "Enter in 'T' for the top 50 most frequent words." << endl;
                    cout << "Enter in 'F' for the file paths." << endl;
                    cout << "Enter in 'H' to display search history." << endl;
                    cout << "Enter in 'C' to clear search history." << endl;
                    cout << "Enter in 'B' to display bookmarks." << endl;
                    cout << "Enter in 'D' to clear bookmarks." << endl;
                    cout << "Enter in 'E' to exit." << endl;
                    cin >> g;
                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');

                    if (g == 'P') {
                        cout << endl;
                        se.readTotalPages();
                        cout << endl;
                    } else if (g == 'W') {
                        cout << endl;
                        cout << "The total number of words is: " << se.numWordsIndexed() << endl;
                        cout << endl;
                    } else if (g == 'T') {
                        cout << endl;
                        se.displayTop50();
                        cout << endl;
                    } else if (g == 'F') {
                        cout << endl;
                        se.readFilePathFromTXTFile();
                        cout << endl;
                    } else if (g == 'H') {
                        if (historyFlag == false) {
                            cout << endl;
                            cout << "There is currently no search history." << endl;
                            cout << endl;
                        } else {
                            cout << endl;
                            se.displayHistory();
                            cout << endl;
                        }
                    } else if(g == 'C') {
                        se.clearHistory();
                        historyFlag = false;
                        cout << endl;
                        cout << "History was cleared." << endl;
                        cout << endl;
                    } else if (g == 'B') {
                        if (bookmarkFlag == false) {
                            cout << endl;
                            cout << "There are currently no bookmarks." << endl;
                            cout << endl;
                        } else {
                            cout << endl;
                            // se.readBookmarks();
                            se.displayBookmarks();
                            cout << endl;
                        }
                    } else if(g == 'D') {
                        se.clearBookmarks();
                        bookmarkFlag = false;
                        cout << endl;
                        cout << "Bookmarks were cleared." << endl;
                        cout << endl;
                    } else if (g == 'E') {
                        s = '?';
                    } else {
                        cout << endl;
                        cout << "Please enter in an appropriate choice. Enter 'T' if you want to try again or 'E' to exit." << endl;
                        cin >> y;
                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                        if (y != 'T') {
                            s = '?';
                        }
                    }
                }

                if(s=='H') {
                    se.chooseStructure('H');
                } else if(s=='A') {
                    se.chooseStructure('A');
                }
                while (s != '?') {
                    cout << endl;
                    cout<<"Please enter a properly formatted boolean query:"<<endl;
                    getline(cin,query);
                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                    cout << "The query results are: " << endl;
                    cout << endl;
                    historyFlag = true;
                    vector<document> vDocs = se.display_search_results(query);
                    se.addToHistory(query);
                    if (vDocs.size() == 0) {
                        cout << "There were no documents found." << endl;
                    }
                    //if there are results
                    if (vDocs.size() > 0) {
                        cout << endl;
                        cout << "Do you wish to bookmark any of the pdfs? If yes, enter 'Y'. If no, enter 'N'." << endl;
                        cin >> b;
                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                        if (b == 'Y') {
                            while (b == 'Y') {
                                cout << endl;
                                cout << "Please select the corresponding number of the pdf you wish to bookmark." << endl;
                                cin >> res;
                                while(cin.fail()) {
                                    cout << endl;
                                    cout << "Error: Please input an appropriate number value." << endl;
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                    cin >> res;
                                    cout << endl;
                                }
                                res--;
                                if (res < vDocs.size()) {
                                    book = vDocs[res].docname;
                                    se.addBookmark(book,query);
                                    bookmarkFlag = true;
                                    cout << endl;
                                    cout << "The pdf was added to Bookmarks." << endl;
                                    cout << endl;
                                } else {
                                    while(res > vDocs.size() || res == vDocs.size()) {
                                        cout << endl;
                                        cout << "Error: Please enter in an appropriate number." << endl;
                                        cin >> res;
                                        while(cin.fail()) {
                                            cout << "Error: Please input an appropriate number value." << endl;
                                            cin.clear();
                                            cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                            cin >> res;
                                        }
                                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                        res--;
                                    }
                                    book = vDocs[res].docname;
                                    se.addBookmark(book,query);
                                    bookmarkFlag = true;
                                    cout << endl;
                                    cout << "The pdf was added to Bookmarks." << endl;
                                    cout << endl;
                                }
                                cout << "Do you wish to bookmark another pdf? If yes, enter 'Y'. If no, enter 'N'." << endl;
                                cin >> p;
                                cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                if (p != 'Y') {
                                    b = 'N';
                                }
                            }
                        }


                        cout << endl;
                        cout << "Do you wish to display the raw text from any of the results? If yes, enter 'Y'. If no, enter 'N'." <<endl;
                        cin>>t;
                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                        if (t == 'Y') {
                            cout << endl;
                            while (t == 'Y') {
                                cout << "Please choose the appropriate file path for the pdf by entering its corresponding number." << endl;
                                vector<string> fVec = se.readFilePathFromTXTFile();
                                cin >> num;
                                while(cin.fail()) {
                                    cout << endl;
                                    cout << "Error: Please input an appropriate number value." << endl;
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                    cin >> num;
                                    cout << endl;
                                }
                                if (num < fVec.size()) {
                                    temp = fVec[num];
                                } else {
                                    while(num > fVec.size()) {
                                        cout << endl;
                                        cout << "Error: Please enter in an appropriate number." << endl;
                                        cin >> num;
                                        while(cin.fail()) {
                                            cout << endl;
                                            cout << "Error: Please input an appropriate number value." << endl;
                                            cin.clear();
                                            cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                            cin >> num;
                                            cout << endl;
                                        }

                                    }
                                    temp = fVec[num];
                                }
                                cout << endl;
                                cout << "Please choose the corresponding number of the pdf to output." << endl;
                                cin >> tt;
                                while(cin.fail()) {
                                    cout << endl;
                                    cout << "Error: Please input an appropriate number value." << endl;
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                    cin >> tt;
                                    cout << endl;
                                }
                                tt--;
                                if (tt < vDocs.size()) {
                                    other = vDocs[tt].docname;
                                } else {
                                    while(tt > vDocs.size() || tt == vDocs.size()) {
                                        cout << endl;
                                        cout << "Error: Please enter in an appropriate number." << endl;
                                        cin >> tt;
                                        while(cin.fail()) {
                                            cout << "Error: Please input an appropriate number value." << endl;
                                            cin.clear();
                                            cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                            cin >> tt;
                                        }
                                        cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                        tt--;
                                    }
                                    other = vDocs[tt].docname;
                                }
                                path = temp + other;
                                boo = se.displayRawFile(path);
                                if (boo == true) {
                                    cout << "Would you like to display another file? Enter 'Y' for yes, 'N' for no." << endl;
                                    cin >> k;
                                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                    if (k != 'Y') {
                                        t = 'N';
                                    }
                                } else {
                                    cout << endl;
                                    cout << "The file or path combination you choose was incorrect. Enter 'T' to try again or 'E' to exit this menu." << endl;
                                    cin >> k;
                                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                                    cout << endl;
                                    if (k == 'E') {
                                        t = 'N';
                                    }
                                }
                            }
                        }

                    }
                    cout << endl;
                    cout << "Would you like to enter another query? Enter 'Y' for yes, 'N' for no." << endl;
                    cin >> q;
                    cin.ignore(std::numeric_limits<streamsize>::max (), '\n');
                    if ( q != 'Y') {
                        s = '?';
                    }
                }
            }
        } else if (d == '0') {
            cout << endl;
            cout << "Thank You for using the PDF Search Engine." << endl;
        } else {
            cout << endl;
            cout << "Error: Please enter in an appropiate choice." << endl;
        }

    }
}
