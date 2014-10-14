#ifndef SIMULATION_H
#define SIMULATION_H
#include "rule.h"
#include "badfileexception.h"
#include "cell.h"
#include <fstream>
#include <iostream>
#define OUT_OF_CELL_SPACE_ERROR 3
using namespace std;

/** \brief Main simulation wrapper
 */
class Simulation
{
    public:
        /** \brief Generate empty simulation
         *
         *
         */
        Simulation();

        virtual ~Simulation();

        /** \brief Loads simulation from file
         *
         * \param filename string Filename with simulation
         * \return void
         * \throw BadFileException In case there was a problem reading file
         */
        void loadFromFile(const string filename) throw (BadFileException);

        /** \brief Get the cell at position, (0,0) is at top-left corner. Using toroidal space.
         *
         * \param x int
         * \param y int
         * \return Cell&
         *
         */
        Cell& cellAt(const int x, const int y) const;

        /** \brief Print all the cells to stout
         *
         * \return void
         *
         */
        void printAll() const;

        /** \brief Recalculates neighbors for each alive, or dead cell
         *
         * \return void
         *
         */
        void recalculateNeighbors();

        /** \brief Makes new cells born and old ones die, assigns newly generated rules by the way
         *
         * \return void
         *
         */
        void action();

    protected:
        //size of simulation area
        int width;
        int height;
        //whole data of cells
        Cell* data;
        //mutation chance in promiles (1/1000)
        int mutationChance;
    private:
};

#endif // SIMULATION_H
