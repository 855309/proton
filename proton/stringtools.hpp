#pragma once
#include <string>
#include <vector>

using namespace std;

vector<string> splitstr(string origin, char delimiter);
vector<string> splitstrcount(string origin, char delimiter, int count);
string deleteAtIndex(string text, int index);
std::string trim(const std::string& s);
string replacestr(string str, string repstr, string substr);