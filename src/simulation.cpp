#include "simulation.h"

Simulation::Simulation()
{
    //nullify array of rules
    for(int i = 0; i < RULE_ARRAY_SIZE; i++)
    {
        rules[i] = nullptr;
    }
}

Simulation::~Simulation()
{
    //clean rules array
    for(int i = 0; i < RULE_ARRAY_SIZE; i++)
    {
        if(rules[i] != nullptr)
        {
            delete(rules[i]);
        }
    }
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
    simulationFile >> width >> height >> ruleCount;
    cout << "Size of simulation area is: " << width << "x" << height << "\n" << ruleCount << " rule(s) are expected" << endl;
    //reading rules
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
        rules[ruleLetter - 'A'] = new Rule(ruleString, ruleLetter);
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
}

Cell& Simulation::cellAt(int x, int y)
{
    return (data[y * width + x]);
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
