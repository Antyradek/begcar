#ifndef RULE_H
#define RULE_H


class Rule
{
    public:
        /** \brief Rule defining 16 logic fields by bits in char
         *
         * \param birth Bits defining births (8-1)
         * \param survive Bits defining survives (8-1)
         *
         */

        Rule(char birth, char survive);
        virtual ~Rule();
    protected:
    private:
};

#endif // RULE_H
