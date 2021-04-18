#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

namespace proton
{
    class logger
    {
    public:
        void Information(std::string infoMessage);
        void Warning(std::string warningMessage);
        void Error(std::string errorMessage);
        void Success(std::string sucMessage);
        void help();
    };
}

#endif