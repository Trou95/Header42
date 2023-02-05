#include "Utils.h"

vector<string> str_split(const string& str, char c)
{
    vector<string> ret;
    int index = 0,last_index = 0;

    while((index = str.find(c,index)) != string::npos)
    {
        if(index - last_index == 1 || index == last_index)
            index = ++last_index;
        else {
            ret.push_back(str.substr(last_index,index - last_index));
            last_index = index;
        }
    }
    if(last_index < str.length())
        ret.push_back(str.substr(last_index));
    return ret;
}