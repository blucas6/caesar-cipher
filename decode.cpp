#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "decode.h"
#include "encode.h"

using namespace std;

string decodeKeyKnown(string alpha, string msg, int key)
{
    string old_msg;
    int curr, i, val;
    for(i=0; i<msg.size(); i++)
    {
        curr = findchar(alpha, msg[i]);
        val = curr - key;
        if (val < 0) { val = val + alpha.size(); }
        old_msg = old_msg + alpha[val];
    }

    return old_msg;
}

void decodeKeyUnknown(string alpha, string msg)
{
    ofstream fp;
    string decodeFile = "decode_msgs.txt";
    fp.open(decodeFile);
    if(fp.is_open())
    {
        string old_msg, tmp_msg;
        for(int i=1; i<alpha.size(); i++)
        {
            tmp_msg = decodeKeyKnown(alpha, msg, i);
            fp << tmp_msg << endl;
        }
        fp.close();
    }
    else
    {
        cout << "Error: Couldn't open " << decodeFile << endl;
        abort();
    }
}

string detectWords(string tmp)
{
    string word, possword, final_msg, print, str_todatabase;
    ifstream database;
    ofstream db;
    ifstream fp;
    int realmsg;
    int counter = 1;
    database.open("WordDatabase.txt");
    if (database.is_open())
    {
        for(int i=0; i<tmp.size(); i++)
        {
            word = word + tmp[i];
            //cout << "building: " << word << endl;
            while(!database.eof())
            {
                getline(database, possword);
                //cout << "possword: " << possword << endl;
                if(possword.compare(word) == 0 && tmp[i+1] == ' ')
                {
                    final_msg.assign(tmp);
                    //cout << "Assigned!" << endl;
                }
            }
            database.clear();
            database.seekg(0);
        }
    }
    else
    {
        cout << "Error: Could not open database!" << endl;
        abort();
    }
    return final_msg;
}

void databaseCleaner()
{
    ifstream db;
    ofstream dbo;
    string tmp;
    int i = 0;
    vector<string> cache;
    db.open("WordDatabase.txt");
    while(!db.eof())
    {
        getline(db, tmp);
        for(;i<cache.size(); i++)
        {
            if(tmp == cache[i])
            {
                break;
            }
        }
        if(i == cache.size())
        {
            cache.push_back(tmp);
        }
        i = 0;
    }
    db.close();
    dbo.open("WordDatabase.txt");
    for(int w=0; w<cache.size(); w++)
    {
        dbo << cache[w] << endl;
    }
    dbo.close();
}

void addToDatabase()
{
    int choice, realmsg, adding;
    ifstream fp;
    ofstream db;
    string print, str_todatabase, build;
    int counter = 1;
    cout << "Would you like to expand my database?" << endl;
            cout << "1. Yes   2. No" << endl << "> ";
            cin >> choice;
            switch (choice)
            {
                case 1:
                fp.open("decode_msgs.txt");
                    while(!fp.eof())
                    {
                        getline(fp, print);
                        cout << counter << ". " << print << endl;
                        counter += 1;
                    }
                    fp.clear();
                    fp.seekg(0);
                    while(adding != 3)
                    {
                        cout << "Please select the real message from the list" << endl << "> ";
                        cin >> realmsg;
                        for(int j=1; j<=realmsg; j++)
                        {
                            getline(fp, str_todatabase);
                        }
                        cout << "Message selected: '" << str_todatabase << "'" << endl;
                        cout << "1. Add to database" << endl;
                        cout << "2. Select different message" << endl;
                        cout << "3. Exit" << endl << "> ";
                        cin >> adding;
                        switch (adding)
                        {
                            case 1:
                                db.open("WordDatabase.txt", ios_base::app);
                                for(int k=0; k<=str_todatabase.size(); k++)
                                {
                                    if(str_todatabase[k] == ' ' || k == str_todatabase.size())
                                    {
                                        db << build << endl;
                                        build.clear();
                                        k += 1;
                                    }
                                    build = build + str_todatabase[k];
                                }
                                db.close();
                                cout << "-Database updated-" << endl;
                                adding = 3;
                                break;
                            case 2:
                                fp.clear();
                                fp.seekg(0);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
            
                default:
                    cout << "-Database unchanged-" << endl;
                    break;
            }
}

string detectMsg()
{
    ifstream fp;
    fp.open("decode_msgs.txt");
    string tmp, final_msg;
    int line = 1;
    if (fp.is_open())
    {
        while(!fp.eof())
        {   
            getline(fp, tmp);
            final_msg = detectWords(tmp);
            //cout << "Final msg for line " << line << ": " << final_msg << endl;
            if(!final_msg.empty())
            {
                return final_msg;
            }
            line += 1;
        }
    }
    else
    {
        cout << "Error: Couldn't open file!" << endl;
        return final_msg;
    }
    fp.close();
    return final_msg;
}