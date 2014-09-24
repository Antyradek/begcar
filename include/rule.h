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
    Rule(string rule);

    /** \brief The letter rule is marked on field with
     *
     * \param
     * \param
     * \return
     *
     */
    char letter;
    virtual ~Rule();

    /** \brief Does the cell survive when having neighborCount neighbors?
     *
     * \param neighborCount int
     * \return bool
     *
     */
    bool survives(int neighborCount);

    /** \brief Does new cell born when having neighborCount
     *
     * \param neighborCount int
     * \return bool
     *
     */
    bool borns(int neighborCount);

    /** \brief Guess what it does...
     *
     *
     */
    bool operator== (const Rule& otherRule) const;

    /** \brief This function generates letter based on rule
     *
     * \return void
     *
     */
    void calculateLetter();

protected:
    bool birth[8];
    bool survive[8];

private:
};

#endif // RULE_H
