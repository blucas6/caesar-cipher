//g++ main.cpp -o main.exe -static-libgcc -static-libstdc++
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <unordered_set>
#include "decode.h"
#include "encode.h"

using namespace std;

int main () 
{
    string msg, final_msg, show_usr, word, msg_brushed;
    int key = 0;
    int word_count = 0;
    string new_msg;
    string old_msg;
    int choice, key_known;
    int prg = 1;
    ifstream db;
    vector<string> words;
    unordered_set<string> uniqueWords;
    ofstream fout;
    int x=0;

    string alpha = "abcdefghijklmnopqrstuvwxyz ";

    ofstream create_database;
    create_database.open("WordDatabase.txt");
    if(create_database.is_open())
    {
        create_database.close();
    }
    else
    {
        cout << "Error: Couldn't create a Word Database" << endl << "Press '1' to exit" << endl;
        cin >> x;
        if(x)
            return 0;
    }

    cout << "Welcome to Ben's Cryptology Program!" << endl;

    while (prg == 1)
    {
        cout << endl << "-Main Menu-" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Encode" << endl;
        cout << "2. Decode" << endl;
        cout << "3. View Supported Characters" << endl;
        cout << "4. Print Word Database" << endl;
        cout << "5. Exit" << endl;
        cout << "6. For testing purposes only" << endl;
        cout << "> ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter your message to encode then press 'Enter'" << endl << "> ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, msg);
                cout << "Enter an encryption key then press 'Enter' to encrypt! (MUST BE LESS THAN " << alpha.size() << ")" << endl << "> ";
                cin >> key;
                if (key < alpha.size()) 
                {
                    msg_brushed = msgBrush(alpha, msg);
                    cout << "Original Message:  '" << msg_brushed << "'" << endl;
                    new_msg = encode(alpha, msg_brushed, key);
                    cout << "Encrypted Message: '" << new_msg << "'" << endl;
                    cout << "Ecryption Key: " << key << endl;
                }
                else
                {
                    cout << "Error: invalid key!" << endl;
                }
                break;
            case 2:
                cout << "Enter your message to decrypt then press 'Enter'" << endl << "> ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, msg);
                cout << "Is the key known?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl << "> ";
                cin >> key_known;
                switch(key_known)
                {
                    case 1:
                        cout << "Enter the decryption key then press 'Enter' to decrypt" << endl << "> ";
                        cin >> key;
                        if (key < 27)
                        {
                            old_msg = decodeKeyKnown(alpha, msg, key);
                            cout << "Decrypted Message: '" << old_msg << "'" << endl;
                        }   
                        else
                        {
                            cout << "Error: invalid key!" << endl;
                        }
                        break;
                    case 2:
                        cout << "Decrypting..." << endl;
                        decodeKeyUnknown(alpha, msg);
                        final_msg = detectMsg();
                        if(!final_msg.empty())
                        {
                            cout << "I found this message: '" << final_msg << "'" << endl;
                        }
                        else
                        {
                            cout << "I did not find any messages" << endl;
                            addToDatabase();
                            databaseCleaner();
                        }
                        break;    
                }
                break;
            
            case 3:
                cout << "Supported Characters: " << alpha << endl;
                break;
            
            case 4:
                cout << endl << "=Word Database=" << endl;
                db.open("WordDatabase.txt");
                if(db.is_open())
                {
                    while(!db.eof())
                    {
                        getline(db, show_usr);
                        if(!show_usr.empty())
                        {
                            cout << "> " << show_usr << endl;
                            word_count += 1;
                        }
                    }
                    cout << endl << "Info: Words learned -> " << word_count << endl;
                    word_count = 0;
                }
                else
                {
                    cout << "Error: Couldn't open Word Database" << endl;
                    cout << "File may be lost or corrupted" << endl;
                }
                db.close();
                break;
            case 5:
                cout << "Exitting..." << endl;
                prg = 0;
                break;

            case 6:
                databaseCleaner();
                break;

            default:
                cout << "That's not one of the choices you ape" << endl;
                break;
        }
    }

    return 0;
}