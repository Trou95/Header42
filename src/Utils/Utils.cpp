#include "Utils.h"

vector<string> str_split(const string& str, char c)
{
    vector<string> ret;
    size_t index = 0,last_index = 0;

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

string str_format(const char* format, ...)
{
    char buffer[256];
    va_list args;

    va_start (args, format);
    vsprintf (buffer,format, args);
    va_end (args);
    return buffer;
}

const string time_to_str(time_t time)
{
    struct tm *local;
    char buffer[20] = {0};

    local = localtime(&time);
    strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", local);
    return string(buffer);
}