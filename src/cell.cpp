#include "cell.h"

Cell::Cell()
{
    alive = false;
    rule = nullptr;
    neighborCount = 0; //for now
}

Cell::Cell(Rule& rule)
{

}

Cell::~Cell()
{
    //dtor
}
