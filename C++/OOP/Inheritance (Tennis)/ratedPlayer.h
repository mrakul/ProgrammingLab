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
        RatedPlayer() : TableTennPlayer(), rating(0) {}
        RatedPlayer(unsigned int r, const string &fName, const string &lName = "NoName", bool tabled = false);
        RatedPlayer(unsigned int r, const TableTennPlayer &tp);     //Construct basing on the base type object
        ~RatedPlayer(){std::cout << "Derived class destructor" << std::endl;};

        virtual void showName() const;      //automatically virtual if virtual in the base class definition
        unsigned int showRating() const { return rating;}   // add a method for derived class + (!) use the implementation of pure virtual function
        //unsigned int showRating() const { return rating; TableTennPlayer::showType;}  // If derived class, the base class's pure function may be called only explicitly with scope resolution
        void resetRating(unsigned int r) { rating = r; } // add a method
        //void showType(void) const; // {std::cout << "This ia a Rated Player";}
        RatedPlayer &operator=(RatedPlayer & ratedPlayer);
};

#endif