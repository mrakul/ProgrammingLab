#include <iostream>
#include "tableTennPlayer.h"

TableTennPlayer::TableTennPlayer() : firstName("NoName"),
                                     lastName("NoName"),
                                     hasTable(false) {}
TableTennPlayer::TableTennPlayer(const string &fName, const string &lName, bool tabled) : firstName(fName),
                                                                                          lastName(lName),
                                                                                          hasTable(tabled) {}

// Functions
void TableTennPlayer::showName() const {
    std::cout << "Usual player " << firstName << ' ' << lastName << ' ';
}

//Virtual functions check
//void TableTennPlayer::showType(void) const {std::cout << "This ia an Ordinary Player";}

TableTennPlayer &TableTennPlayer::operator=(TableTennPlayer & tennPlayer){
    this->firstName = tennPlayer.firstName;
    this->lastName = tennPlayer.lastName;
    this->hasTable = tennPlayer.hasTable;
    return *this;
}