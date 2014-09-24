#include <iostream>
#include <thread> //wait few seconds
#include <chrono> //know the time to wait
#include "rule.h"
#include "simulation.h"
#include "cell.h"
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
    for(int i = 0; i < 1000; i++)
    {
        simulation.recalculateNeighbors();
        simulation.action();
        this_thread::sleep_for (chrono::milliseconds(200));
        cout << "\033[2J"; //ANSI escape code - clear screen
        simulation.printAll();
    }

    return 0;
}
