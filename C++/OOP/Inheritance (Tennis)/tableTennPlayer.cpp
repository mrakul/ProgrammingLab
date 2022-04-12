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