#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int findchar(string alpha, char c)
{
    int j;
    for(j=0; j<alpha.size(); j++)
    {
        if(alpha[j] == c)
        {
            return j;
        }
    }
    return -1;
}

string encode(string alpha, string msg, int key)
{
    int curr, val;
    string new_msg;
    for(int i=0; i<msg.size(); i++)
    {
        curr = findchar(alpha, msg[i]);
        if(curr == -1) 
        {
            break;
        }
        else
        {
            val = key + curr;
            if(val > (alpha.size()-1)) { val = val - alpha.size(); }
            //cout << "msg[i]: " << msg[i] << " curr: " << curr << " val: " << val << endl;
            new_msg = new_msg + alpha[val];
        }
    }
    return new_msg;
}

int lowercaseinator(string alpha, char c)
{
    string upper_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0; i<upper_alpha.size(); i++)
    {
        if(upper_alpha[i] == c)
        {
            return i;
        }
    }
    return -1;
}

string msgBrush(string alpha, string &msg)
{
    string new_msg;
    int tmp;
    for(int i=0; i<msg.size(); i++)
    {
        if(findchar(alpha, msg[i]) == -1)
        {
            tmp = lowercaseinator(alpha, msg[i]);
            if(tmp != -1)
            {
                new_msg = new_msg + alpha[tmp];
            }
        }
        else
        {
            new_msg = new_msg + msg[i];
        }
    }
    return new_msg;
}