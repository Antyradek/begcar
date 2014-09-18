#ifndef SIMULATION_H
#define SIMULATION_H
#include "rule.h"
#include "filenotfoundexception.h"
#include "cell.h"
#include <fstream>
#include <iostream>
#define RULE_ARRAY_SIZE 26
using namespace std;

/** \brief Main simulation wrapper
 */
class Simulation
{
    public:
        Simulation();
        virtual ~Simulation();
        /** \brief Loads simulation from file
         *
         * \param filename string Filename with simulation
         * \return void
         *
         */
        void loadFromFile(string filename) throw (FileNotFoundException);
    protected:
        //size of simulation area
        int width;
        int height;
        //rules for each ASCII letter
        Rule* rules[RULE_ARRAY_SIZE];
        //whole data of cells
        Cell** data;
    private:
};

#endif // SIMULATION_H
