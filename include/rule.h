#ifndef RULE_H
#define RULE_H
#include <string>
#include <iostream>
using namespace std;

/** \brief Rule defining B/S and mark
 */
class Rule
{
    public:

        /** \brief Rule created from string of the format "3/23", or "/12345678", or "3/32"
         *
         * \param rule string String with '/' inside
         *
         */
        Rule(string rule, char letter);
        virtual ~Rule();
    protected:
        bool birth[8];
        bool survive[8];
        char letter;
    private:
};

#endif // RULE_H
