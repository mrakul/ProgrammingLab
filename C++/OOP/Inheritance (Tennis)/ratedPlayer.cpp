#include <iostream>
#include "ratedPlayer.h"

RatedPlayer::RatedPlayer(unsigned int r, const string &fn, const string &ln, bool ht) : TableTennPlayer(fn, ln, ht), rating(r) {}
// If omit TableTennPlayer(fn, ln, ht) constructor, then default TableTennPlayer() is called implicitly:
// RatedPlayer::RatedPlayer(unsigned int r, const string &fn, const string &ln, bool ht) : TableTennPlayer(), rating(r){}


//Constructor using base object type to construct derived object
RatedPlayer::RatedPlayer(unsigned int r, const TableTennPlayer &tp) :  TableTennPlayer(tp), rating(r)   //rating(r), TableTennPlayer(tp) gives warning that rating will e initialized after TableTennPlayer(tp)
{   }

// Functions
void RatedPlayer::showName() const {
   TableTennPlayer::showName();
   std::cout << " (rated player also)";
}

RatedPlayer &RatedPlayer::operator=(RatedPlayer & ratedPlayer){
   this->rating = ratedPlayer.rating;
   return *this;
}

//void RatedPlayer::showType(void) const {std::cout << "This ia a Rated Player";}