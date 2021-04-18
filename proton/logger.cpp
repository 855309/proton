#include <iostream>
#include <string>

#include "logger.hpp"
#include "color.hpp"

using namespace proton;

void logger::Information(std::string infoMessage)
{
    std::cout << dye::white("proton: ") << dye::aqua("info: ") << infoMessage << std::endl;
}

void logger::Warning(std::string warningMessage)
{
    std::cout << dye::white("proton: ") << dye::yellow("warning: ") << warningMessage << std::endl;
}

void logger::Error(std::string errorMessage)
{
    std::cout << dye::white("proton: ") << dye::red("error: ") << errorMessage << std::endl;
}

void logger::Success(std::string sucMessage)
{
    std::cout << dye::white("proton: ") << dye::green("success: ") << sucMessage << std::endl;
}

void logger::help()
{
    std::cout
        << dye::yellow("proton") << ": fast interpreted language with cool stuff." << std::endl
        << std::endl
        << "usage:" << std::endl
        << "proton <pfcPath>" << std::endl
        << std::endl
        << "(c) OpenC Software Technologies Corporation 2021" << std::endl;
}