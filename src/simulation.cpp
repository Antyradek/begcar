#include "simulation.h"

Simulation::Simulation()
{

}

Simulation::~Simulation()
{
    //clean data array
    delete[] data;
}

void Simulation::loadFromFile(const string filename) throw(BadFileException)
{
    //opening the file
    ifstream simulationFile(filename, ifstream::in);
    if(!simulationFile.good())
    {
        cout << "Error opening the file." << endl;
        throw(BadFileException());
    }

    cout << "Opening " + filename << endl;
    int ruleCount;

    //reading initial data
    simulationFile >> width >> height >> mutationChance >> ruleCount;
    if(!simulationFile.good())
    {
        cout << "Error while reading initial conditions." << endl;
        throw(BadFileException());
    }
    cout << "Size of simulation area is: " << width << "x" << height << "\n" << "mutation chance: " << mutationChance << " promiles\n" << ruleCount << " rule(s) are expected" << endl;

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
        if(!simulationFile.good())
        {
            cout << "Error reading rule " << i + 1 << endl;
            throw(BadFileException());
        }
        if(uselessEquationMark != '=')
        {
            cout << "Error while reading rules! It seems " << uselessEquationMark << " is not \'=\'." << endl;
            throw(BadFileException());
        }
        if(ruleLetter > 'Z' || ruleLetter < 'A')
        {
            cout << "Error while reading rules! It seems rule name is not a capital letter." << endl;
            throw(BadFileException());
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
        if(!simulationFile.good())
        {
            cout << "Unable to read data grid." << endl;
            throw(BadFileException());
        }
        if((int)row.length() < width)
        {
            cout << "Not enough characters in data grid!" << endl;
            throw(BadFileException());
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

Cell& Simulation::cellAt(const int x, const int y) const
{
    return (data[((y + height) % height) * width + ((x + width) % width)]);
    //return (data[y * width + x]);
}

void Simulation::printAll() const
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

