#include "rule.h"


Rule::Rule(string rule, char letter)
{
    //cleaning bool arrays
    for(int i = 0; i < 8; i++)
    {
        birth[i] = false;
        survive[i] = false;
    }
    clog << "Creating new rule: " << rule << " with letter: " << letter << endl;
    this -> letter = letter;
    int ruleLength = rule.length();
    bool* readingValues = birth; //pointer to the array we are at first putting our values in
    for(int i = 0; i < ruleLength; i++)
    {
        char ichar = rule[i];
        if(ichar == '/')
        {
            readingValues = survive; //now we are reading the rest
            continue;
        }
        readingValues[ichar - '1'] = true;
    }
    clog << "Read rule: \n12345678|12345678\n";
    for(int i = 0; i < 8; i++)
    {
        if(birth[i]) clog << 'X';
        else
            clog << ' ';
    }
    clog << '|';
    for(int i = 0; i < 8; i++)
    {
        if(survive[i]) clog << 'X';
        else
            clog << ' ';
    }
    clog << endl;
}

Rule::~Rule()
{
    //dtor
}
