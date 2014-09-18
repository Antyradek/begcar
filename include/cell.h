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


        virtual ~Cell();

        /** \brief Add parent with a rule
         *
         * \param rule Rule* Rule of a parent
         * \return void
         *
         */
        void addNeighbor(Rule* rule);

        /** \brief Make cell alive and set a rule to it
         *
         * \param rule Rule*
         * \return void
         *
         */
        void bornWithRule(Rule* rule);

        /** \brief Make a cell dieeeeeeeee! Mwahahaha!
         *
         * \return void
         *
         */
        void kill();

        /** \brief Gives a character displaying this cell
         *
         * \return char Rule character, or ' ' if dead
         *
         */
        char getRuleChar();

        //is the cell alive
        bool alive;

        Rule* rule;
    protected:
        //how many neighbors does cell have
        int neighborCount;

        //what rules have neighbors
        Rule* neighborRules[8];

    private:
};

#endif // CELL_H
