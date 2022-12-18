#include "tableTennPlayer.h"
#include "ratedPlayer.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    //Base class objects and functions calls
    TableTennPlayer simplePlayer1 {"Michael", "Pims", true};
    TableTennPlayer simplePlayer2 {"John", "Lane", false};
    simplePlayer1.showName();
    simplePlayer1.HasTable() ? std::cout << "has table " : std::cout << " has no table ";
    std::cout << std::endl;
    simplePlayer2.showName();
    simplePlayer2.HasTable() ? std::cout << "has table " : std::cout << " has no table ";
    std::cout << std::endl;

    //Derived class objects
    RatedPlayer ratedPlayer1 {5, simplePlayer1};                            // (!) use copy constructor with the base object type
    RatedPlayer ratedPlayer2 {10 , "Cringe", "Dinge", false};               // Calls the RatedPlayer with 4 arguments constructor -> TableTennPlayer with 3 arguments constructor
    RatedPlayer ratedPlayer3 = ratedPlayer2;                                // (!)Use the Copy constuctor: The same as write: RatedPlayer ratedPlayer3 = RatedPlayer(ratedPlayer2).

    ratedPlayer1.showRating();                                              //  Can be called directly by the object
    ratedPlayer2.showName();
    ratedPlayer3.showName();
    std::cout << ratedPlayer3.showRating() << '\n';

    //Examples of virtual functions calls
    TableTennPlayer &refSimplePlayer1 = simplePlayer1;
    TableTennPlayer &refRatedPlayer1 = ratedPlayer1;
    TableTennPlayer *ptrRatedPlayer1 = &ratedPlayer1;       // By pointer

    refSimplePlayer1.showName();                            // OK
    refRatedPlayer1.showName();                             // Call overriden function (since it is virtual)
    ptrRatedPlayer1->showName();                            // Call overriden function by using pointer

    //Assignment operator checks
    refRatedPlayer1 = refSimplePlayer1;                     // refRatedPlayer1.operator=(refSimplePlayer1);     => uses Base class operator=
    refSimplePlayer1 = refRatedPlayer1;                     // refSimplePlayer1.operator=(refRatedPlayer1);     => uses Base class operator=
    refRatedPlayer1 = refRatedPlayer1;                      // Uses Base class assignment
    simplePlayer1 = ratedPlayer1;                           // Uses Base class assignment
    //ratedPlayer1 = simplePlayer1;
    ratedPlayer1 = ratedPlayer2;                            // Uses only (!) the derived class assignment if op= specified.
                                                            // (!!!) And if op= not specified, uses default RatedPlayer and then op= of the TableTennPlayer

    // refRatedPlayer1.showRating();                        // Methods of inherited class can't be called neither
    // ptrRatedPlayer1->showRating();                       // by using a reference nor by using a pointer

    /* Dynamic memory allocation + virtual destructor testing */
    // 1. If TableTennPlayer's destructor is virtual first call the Derived Class Destructor, and then the Base Class's Destructor
    // 2. If TableTennPlayer's destructor is NOT virtual, only the Base Class's Destructor is called if use pointers to the Base Class
    // (actually, for this case, the gcc's message arising with -Werror flag:
    // "deleting object of polymorphic class type 'TableTennPlayer' which has non-virtual destructor might cause undefined behavior [-Werror=delete-non-virtual-dtor]")
    TableTennPlayer *players[2];                                            // Create array of pointers to TableTennPlayers
    RatedPlayer *ratedPlayer = new RatedPlayer{7, "Player6", "Grizzly", false};

    players[0] = new TableTennPlayer{"Player4", "Man", true};
    players[1] = new RatedPlayer{5, "Player5", "Woman", false};

    delete players[0];
    delete players[1];      // Since the base Destructor is virtual, first call the derived class Destructor, and then the base class's Destructor

    // Check for the RatedPlayer pointer: !!! even if the Base Class's Destructor is not virtual, deleting ratedPlayer results in calling Derived Destructor and then the Base Destructor
    // And if the destructor is virtual, the same effect since the pointer to the Derived Class
    delete ratedPlayer;

    return 0;
}
