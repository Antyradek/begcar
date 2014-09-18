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
    for(int i = 0; i < RULE_ARRAY_SIZE; i++)
    {
        if(rules[i] != nullptr)
        {
            delete(rules[i]);
        }
    }
}

void Simulation::loadFromFile(string filename) throw(FileNotFoundException)
{
    fstream simulationFile(filename, fstream::in);
    if(!simulationFile.good()) throw(FileNotFoundException());
    cout << "Opening " + filename << endl;
    int ruleCount;
    simulationFile >> width >> height >> ruleCount;
    cout << "Size of simulation area is: " << width << "x" << height << "\n" << ruleCount << " rule(s) are expected" << endl;
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


    simulationFile.close();
}
