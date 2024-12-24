#ifndef ENCODE_
#define ENCODE_

#include <string>

int findchar(std::string alpha, char c);

std::string encode(std::string alpha, std::string msg, int key);

int lowercaseinator(std::string alpha, char c);

std::string msgBrush(std::string alpha, std::string &msg);

#endif