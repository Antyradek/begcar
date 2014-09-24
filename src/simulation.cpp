#include "simulation.h"

Simulation::Simulation()
{

}

Simulation::~Simulation()
{
    //clean data array
    delete[] data;
}

void Simulation::loadFromFile(string filename) throw(FileNotFoundException)
{
    fstream simulationFile(filename, fstream::in);
    if(!simulationFile.good()) throw(FileNotFoundException());
    cout << "Opening " + filename << endl;
    int ruleCount;
    //reading initial data
    simulationFile >> width >> height >> mutationChance >> ruleCount;
    cout << "Size of simulation area is: " << width << "x" << height << "\n" << "mutation chance: " << mutationChance << " promiles\n" << ruleCount << "rule(s) are expected" << endl;
    //reading rules
    Rule* rules[26];
    for(int i = 0; i < 26; i++)
    {
        rules[i] = nullptr;
    }
    for(int i = 0; i < ruleCount; i++)
    {
        char ruleLetter;
        char uselessEquationMark;
        string ruleString;
        simulationFile >> ruleLetter >> uselessEquationMark >> ruleString;
        if(uselessEquationMark != '=')
        {
            cout << "Error while reading rules! It seems " << uselessEquationMark << " is not \'=\'=." << endl;
            throw(FileNotFoundException());
        }
        if(ruleLetter > 'Z' || ruleLetter < 'A')
        {
            cout << "Error while reading rules! It seems rule name is not a capital letter." << endl;
            throw(FileNotFoundException());
        }
        cout << "Read " << ruleString << " marked with " << ruleLetter << endl;
        rules[ruleLetter - 'A'] = new Rule(ruleString);
    }
    //reading data
    data = new Cell[width * height]; //array of dead cells in row
    for(int i = 0; i < height; i++)
    {
        //reading row by row
        string row;
        simulationFile >> row;
        if((int)row.length() < width)
        {
            cout << "Not enough characters in data grid!" << endl;
            throw(FileNotFoundException());
        }
        for(int j = 0; j < width; j++)
        {
            char letter = row[j];
            if(letter > 'A' && letter < 'Z')
            {
                //found character, we have to born new cell with that rule here
                cellAt(j,i).bornWithRule(new Rule(*rules[letter - 'A']));
            }
        }
    }
    simulationFile.close();
    for(int i = 0; i < 26; i++)
    {
        if(rules[i] != nullptr)
            delete(rules[i]);
    }
}

Cell& Simulation::cellAt(int x, int y)
{
    return (data[(y % height) * width + (x % width)]);
    //return (data[y * width + x]);
}

void Simulation::printAll()
{
    //it goes row after row
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            cout << cellAt(x,y).getRuleChar();
        }
        cout << endl;
    }
}

void Simulation::recalculateNeighbors()
{
    //clear neighbors number first
    for(int i = 0; i < width * height; i++)
    {
        data[i].resetNeighbors();
    }
    //if cell is alive, it informs their neighbors about existence
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(cellAt(x,y).alive)
            {
                Rule* cellRule = cellAt(x,y).rule;
                //going clockwise from left
                cellAt(x - 1, y).addNeighbor(cellRule);
                cellAt(x - 1, y - 1).addNeighbor(cellRule);
                cellAt(x, y - 1).addNeighbor(cellRule);
                cellAt(x + 1, y - 1).addNeighbor(cellRule);
                cellAt(x + 1, y).addNeighbor(cellRule);
                cellAt(x + 1, y + 1).addNeighbor(cellRule);
                cellAt(x, y + 1).addNeighbor(cellRule);
                cellAt(x - 1, y + 1).addNeighbor(cellRule);
            }
        }
    }
}

void Simulation::action()
{
    for(int i = 0; i < width * height; i++)
    {
        data[i].action(mutationChance);
    }
}

