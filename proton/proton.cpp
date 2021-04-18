#include <iostream>
#include <string.h>
#include <vector>

#include "logger.hpp"
#include "executer.hpp"

using namespace std;

int main(int argc, char** argv)
{
    proton::logger log;

    if(argc != 2)
    {
        log.Error("Please specify the inputPath parameter.");
        
        cout << endl;

        log.help();
        return -1;
    }

    string inputFilePath = argv[1];

    proton::executer exec;

    exec.executeProgram(inputFilePath);

    return 0;
}
