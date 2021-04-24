#include <iostream>
#include <string>

#include "logger.hpp"

using namespace proton;

void logger::Information(std::string infoMessage)
{
    std::cout << "proton: " << "info: " << infoMessage << std::endl;
}

void logger::Warning(std::string warningMessage)
{
    std::cout << "proton: " << "warning: " << warningMessage << std::endl;
}

void logger::Error(std::string errorMessage)
{
    std::cout << "proton: " << "error: " << errorMessage << std::endl;
}

void logger::Success(std::string sucMessage)
{
    std::cout << "proton: " << "success: " << sucMessage << std::endl;
}

void logger::help()
{
    std::cout
        << "proton" << ": fast interpreted language with cool stuff." << std::endl
        << std::endl
        << "usage:" << std::endl
        << "proton <pfcPath>" << std::endl
        << std::endl
        << "(c) OpenC Software Technologies Corporation 2021" << std::endl;
}