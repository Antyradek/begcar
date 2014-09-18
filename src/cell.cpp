#include "cell.h"

Cell::Cell()
{
    alive = false;
    rule = nullptr;
    neighborCount = 0; //for now
}


Cell::~Cell()
{
    if(rule != nullptr)
    {
        delete(rule);
    }
}

void Cell::bornWithRule(Rule* rule)
{
    if(this -> rule != nullptr)
    {
        //this should never happen, but you know...
        delete(this -> rule);
    }

    this -> rule = rule;
    alive = true;
}

void Cell::kill()
{
    alive = false;
    if(rule != nullptr)
    {
        delete(rule);
    }
}

char Cell::getRuleChar()
{
    if(!alive) return ' ';
    else
        return rule -> letter;
}
