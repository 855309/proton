#include "stringtools.hpp"

#include <string>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

char* strtocharptr(string str)
{
	return &str[0];
}

vector<string> splitstr(string origin, char delimiter)
{
    string text = origin + delimiter;

    stringstream stream;
    vector<string> strVector;

    for (auto c : text)
    {
        if (c == delimiter)
        {
            strVector.push_back(stream.str());
            stream.str("");
        }
        else
        {
            stream << c;
        }
    }

    return strVector;
}

vector<string> splitstrcount(string origin, char delimiter, int count)
{
    string text = origin;

    stringstream stream;
    vector<string> strVector;

    bool finished = false;

    for (auto c : text)
    {
        if (strVector.size() == count)
        {
            finished = true;
        }

        if (c == delimiter)
        {
            if (finished)
            {
                stream << c;
            }
            else
            {
                strVector.push_back(stream.str());
                stream.str("");
            }
        }
        else
        {
            stream << c;
        }
    }

    strVector.push_back(stream.str());

    return strVector;
}

string deleteAtIndex(string text, int index)
{
    stringstream stream;

    for(int i = 0; i < text.length(); i++)
    {
        if(index != i)
        {
            stream << text[i];
        }
    }

    return stream.str();
}

std::string trim(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

string replacestr(string argstr, string repstr, string substr)
{
    int index;

    string str = argstr;

    while ((index = str.find(repstr)) != string::npos)
    {
        str.replace(index, substr.length(), substr);
    }

    return str;
}