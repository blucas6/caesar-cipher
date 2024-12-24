#ifndef DECODE_
#define DECODE_

#include <string>
#include <fstream>
using namespace std;

string decodeKeyKnown(string alpha, string msg, int key);

void decodeKeyUnknown(string alpha, string msg);

string detectMsg();

void addToDatabase();

string detectWords(string tmp);

void databaseCleaner();

#endif