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

        /** \brief Get the cell at position, (0,0) is at top-left corner
         *
         * \param x int
         * \param y int
         * \return Cell&
         *
         */
        Cell& cellAt(int x, int y);

        /** \brief Print all the cells
         *
         * \return void
         *
         */
        void printAll();
    protected:
        //size of simulation area
        int width;
        int height;
        //rules for each ASCII letter
        Rule* rules[RULE_ARRAY_SIZE];
        //whole data of cells
        Cell* data;
    private:
};

#endif // SIMULATION_H
