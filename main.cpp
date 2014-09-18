#include <iostream>
#include "rule.h"
#include "simulation.h"
#define NO_FILE_SPECIFIED_ERROR 1
#define CANT_OPEN_FILE_ERROR 2

using namespace std;

void printHelpAndExit()
{
    cout << "USAGE:\nGive filename of simulation" << endl;
    exit(NO_FILE_SPECIFIED_ERROR);
}

int main(int argCount, char** args)
{
    if(argCount < 2) printHelpAndExit();

    cout << "Welcome in BEGCAR, name of executable: " << args[0] << endl;
    Simulation simulation;
    try
    {
        simulation.loadFromFile(args[1]);
    }
    catch(FileNotFoundException e)
    {
        cout << "Cannot open file: " + (string)args[1] << endl;
        exit(CANT_OPEN_FILE_ERROR);
    }
    simulation.printAll();

    return 0;
}
