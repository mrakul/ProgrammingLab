#ifndef RATEDPLAYER_H_
#define RATEDPLAYER_H_
#include <string>
#include "tableTennPlayer.h"
using std::string;

class RatedPlayer : public TableTennPlayer
{
    private:
        unsigned int rating; // add new member

    public:
        RatedPlayer(unsigned int r = 0, const string &fn = "none", const string &ln = "none", bool ht = false);
        RatedPlayer(unsigned int r, const TableTennPlayer &tp);     //Construct basing on the base type object
        ~RatedPlayer(){std::cout << "Derived class destructor" << std::endl;};

        virtual void showName() const;      //automatically virtual if virtual in the base class definition
        unsigned int showRating() const { return rating; }   // add a method
        void resetRating(unsigned int r) { rating = r; } // add a method
};

#endif