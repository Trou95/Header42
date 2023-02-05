#pragma once

#include <cstdlib>
#include <stdarg.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <filesystem>

using std::string;
using std::vector;
using std::set;
using std::unordered_set;


vector<string> str_split(const string& str, char c);
string str_format(const char* format, ...);
const string time_to_str(time_t time);