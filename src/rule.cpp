#include "rule.h"


Rule::Rule(string rule)
{
    //cleaning bool arrays
    for(int i = 0; i < 8; i++)
    {
        birth[i] = false;
        survive[i] = false;
    }
    //clog << "Creating new rule: " << rule << endl;
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
    /*clog << "Read rule: \n12345678|12345678\n";
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
    clog << endl;*/
    calculateLetter();
}

Rule::~Rule()
{
    //dtor
}

bool Rule::survives(const int neighborCount) const
{
    if(neighborCount > 8 || neighborCount < 1) return false;
    //survive[0] holds info about survival for 1 neighbor
    return(survive[neighborCount - 1]);
}

bool Rule::borns(const int neighborCount) const
{
    if(neighborCount > 8 || neighborCount < 1) return false;
    return(birth[neighborCount - 1]);
}

bool Rule::operator== (const Rule& otherRule) const
{
    for(int i = 0; i < 8; i++)
    {
        if(birth[i] != otherRule.birth[i] || survive[i] != otherRule.survive[i])
        {
            return false;
        }
    }
    return true;
}

void Rule::calculateLetter()
{
    //creating a 16bit number, whose binary representation is birth|survive from 1 to 8
    int ruleInt = 0;
    if(birth[0]) ruleInt += 0x8000;
    if(birth[1]) ruleInt += 0x4000;
    if(birth[2]) ruleInt += 0x2000;
    if(birth[3]) ruleInt += 0x1000;
    if(birth[4]) ruleInt += 0x800;
    if(birth[5]) ruleInt += 0x400;
    if(birth[6]) ruleInt += 0x200;
    if(birth[7]) ruleInt += 0x100;

    if(survive[0]) ruleInt += 0x80;
    if(survive[1]) ruleInt += 0x40;
    if(survive[2]) ruleInt += 0x20;
    if(survive[3]) ruleInt += 0x10;
    if(survive[4]) ruleInt += 0x8;
    if(survive[5]) ruleInt += 0x4;
    if(survive[6]) ruleInt += 0x2;
    if(survive[7]) ruleInt += 0x1;
    //letter will be capital letter
    letter = ruleInt % 26 + 'A';
}
