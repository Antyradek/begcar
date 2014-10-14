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
         *
         */
        void addNeighbor(Rule* rule);

        /** \brief Make cell alive and set a rule to it
         *
         * \param newRule Rule*
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
        char getRuleChar() const;

        /** \brief Sets neighborCount to 0 and nulls neighborRules array
         *
         * \return void
         *
         */
        void resetNeighbors();

        /** \brief Kill, or born new cells based on neighbors
         *
         * \param mutationChance int Mutation chance in promiles (1/1000)
         *
         */
        void action(const int mutationChance);

        //is the cell alive
        bool alive;

        //remember, that cell needs to hold previous rule, even when dead, to that neighbors point to it
        Rule* rule;

        //how many neighbors does the cell have
        int neighborCount;

    protected:
        //what rules have neighbors
        Rule* neighborRules[8];

    private:
};

#endif // CELL_H
