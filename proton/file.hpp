#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace proton
{
    class file
    {
    public:
        std::vector<std::string> ReadAllLines(std::string path);
        bool WriteAllText(std::string path, std::string text);
    };
}
