#pragma once

#include <cstdlib>

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
const string time_to_str(time_t time);