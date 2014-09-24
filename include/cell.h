#ifndef CELL_H
#define CELL_H
#include "rule.h"
#include<chrono> //time seed for generator
#include<random> //random generator
#include<iostream> //log

using namespace std;

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

        /** \brief Add neighbor with a rule
         *
         * \param rule Rule* Rule of a neighbor
         * \return void
         *
         */
        void addNeighbor(Rule* rule);

        /** \brief Make cell alive and set a rule to it
         *
         * \param newRule Rule*
         * \return void
         *
         */
        void bornWithRule(Rule* newRule);

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

        /** \brief Sets neighborCount to 0 and nulls neighborRules array
         *
         * \return void
         *
         */
        void resetNeighbors();

        /** \brief The same as action, but allows born cells to mutate
         *
         * \param mutationChance int Mutation chance in promiles (1/1000)
         * \return Rule* The new rule this cell is born with, or null if it died
         *
         */
        void action(int mutationChance);

        //is the cell alive
        bool alive;
        //remember, that cell needs to hold previous rule, even when dead, to that neighbors point to it
        Rule* rule;

        //how many neighbors does cell have
        int neighborCount;

    protected:
        //what rules have neighbors
        Rule* neighborRules[8];

    private:
};

#endif // CELL_H
