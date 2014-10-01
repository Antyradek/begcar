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
    cout << "USAGE:\nGive filename of simulation\nOptional speed in miliseconds - default 200" << endl;
    exit(NO_FILE_SPECIFIED_ERROR);
}

int main(int argCount, char** args)
{
    if(argCount < 2) printHelpAndExit();
    cout << "Welcome in BEGCAR, name of executable: " << args[0] << endl;
    int speed = 200;
    if(argCount == 3)
    {
        speed = stoi(args[2]);
    }
    Simulation simulation;
    try
    {
        simulation.loadFromFile(args[1]);
    }
    catch(BadFileException e)
    {
        cout << "Error reading file: " + (string)args[1] << endl;
        exit(CANT_OPEN_FILE_ERROR);
    }
    simulation.printAll();
    while(true)
    {
        simulation.recalculateNeighbors();
        simulation.action();
        this_thread::sleep_for (chrono::milliseconds(speed));
        cout << "\033[2J"; //ANSI escape code - clear screen
        simulation.printAll();
    }

    return 0;
}
