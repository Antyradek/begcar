#ifndef CELL_H
#define CELL_H
#include "rule.h"

/** \brief Represents single cell on field
 */
class Cell
{
    public:

        /** \brief Creating cell without rule gives dead one
         *
         *
         */
        Cell();

        Cell(Rule& rule);

        virtual ~Cell();

        /** \brief Add parent with a rule
         *
         * \param rule Rule* Rule of a parent
         * \return void
         *
         */
        void addNeighbor(Rule* rule);

        //is the cell alive
        bool alive;

    protected:
        //how many neighbors does cell have
        int neighborCount;

        //what rules have neighbors
        Rule* neighborRules[8];

        Rule* rule;
    private:
};

#endif // CELL_H
