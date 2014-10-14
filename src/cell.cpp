#include "cell.h"

Cell::Cell()
{
    alive = false;
    rule = nullptr;
    neighborCount = 0; //for now
    for(int i = 0; i < 8; i++)
    {
        neighborRules[i] = nullptr;
    }
}


Cell::~Cell()
{
    if(rule != nullptr)
        delete(rule);
}

void Cell::bornWithRule(Rule* newRule)
{
    if(rule != nullptr)
        delete(rule);
    rule = newRule;
    alive = true;
}

void Cell::kill()
{
    alive = false;
}

char Cell::getRuleChar() const
{
    if(!alive) return ' ';
    else
        return rule -> letter;
}

void Cell::addNeighbor(Rule* rule)
{
    neighborCount++;
    neighborRules[neighborCount - 1] = rule;
}

void Cell::resetNeighbors()
{
    neighborCount = 0;
    for(int i = 0; i < 8; i++)
    {
        neighborRules[i] = nullptr;
    }
}

void Cell::action(const int mutationChance)
{
     //life after death
    if(alive && !rule -> survives(neighborCount))
    {
        kill();
        //clog << "Cell Died" << endl;
        return;
    }
    if(alive && rule -> survives(neighborCount))
    {
        //cell is alive and survives well
        //clog << "Cell Survived" << endl;
        return;
    }
    if(neighborCount == 0)
    {
        //cell is dead and has no neighbors, so it won't get alive anytime soon
        return;
    }
    Rule* matchingRules[8];
    for(int i = 0; i < 8; i++)
    {
        matchingRules[i] = nullptr;
    }
    int matchingRulesCounter = 0;
    //for each neighbor, we check if it can take part in new birth
    for(int i = 0; i < neighborCount; i++)
    {
        if(neighborRules[i] -> borns(neighborCount))
        {
            //yes, it takes part in birth, we save this rule to the matchingRules
            matchingRulesCounter++;
            matchingRules[matchingRulesCounter - 1] = neighborRules[i];
        }
    }
    if(matchingRulesCounter == 0)
    {
        //no-one of neighbors can born this cell
        return;
    }
    //here we need to mix the matching rules in random way and mutate them
    //setting the random generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    minstd_rand0 generator (seed);  // minstd_rand0 is a standard linear_congruential_engine
     //generator()
    //first birth rule
    string birth = "";
    for(int i = 0; i < 8; i++)
    {
        int rand = generator();
        if(rand % 1000 < mutationChance)
        {
            //mutate
            if(rand % 2)
            {
                //forcing the rule for that i
                birth += (char)(i + '1');
            }
            continue;
        }
        //no mutation
        //the random matching neighbor will give a field from it's rule
        Rule* parentRule = matchingRules[rand % matchingRulesCounter];
        if(parentRule -> borns(i + 1))
        {
            birth += (char)(i + '1');
        }
    }
    //secondly survival rule
    string survival = "";
    for(int i = 0; i < 8; i++)
    {
        int rand = generator();
        if(rand % 1000 < mutationChance)
        {
            //mutate
            if(rand % 2)
            {
                //forcing the rule for that i
                survival += (char)(i + '1');
            }
            continue;
        }
        //no mutation
        //the random neighbor will give a field from it's rule
        Rule* parentRule = matchingRules[rand % matchingRulesCounter];
        if(parentRule -> survives(i + 1))
        {
            survival += (char)(i + '1');
        }
    }
    string finalRule = birth + '/' + survival;
    //now we have to assign this rule
    Rule* newRule = new Rule(finalRule);
    bornWithRule(newRule);
    //clog << "Cell Borned" << endl;
}
