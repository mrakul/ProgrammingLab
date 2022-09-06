#include "tableTennPlayer.h"
#include "ratedPlayer.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    //Base class objects and functions calls
    TableTennPlayer player1 {"Michael", "Pims", true};
    TableTennPlayer player2 {"John", "Lane", false};
    player1.showName();
    player1.HasTable() ? std::cout << "has table " : std::cout << " has no table ";
    std::cout << std::endl;
    player2.showName();
    player2.HasTable() ? std::cout << "has table " : std::cout << " has no table ";
    std::cout << std::endl;

    //Derived class objects
    RatedPlayer player3 {5, player1};   //(!) use copy constructor with the base object type
    RatedPlayer player4 = RatedPlayer{10 , "Cringe", "Dinge", false};       //Calls the RatedPlayer with 4 argunments constructor -> TableTennPlayer with 3 arguments constructor
    RatedPlayer player5 = player4; //(!)Use the Copy constuctor: The same as wrigint RatedPlayer player5 = RatedPlayer(player4).
    player3.showRating();               // Can be called directly by the object

    //Examples of virtual functions calls
    TableTennPlayer &r_pl1 = player1;
    TableTennPlayer &r_pl3 = player3;
    TableTennPlayer * ptr_pl3 = &player3;       //By pointer

    r_pl1.showName();                   //OK
    r_pl3.showName();                   //Call overloaded function (since it is virtual)
    ptr_pl3->showName();                //Call overloaded function by using pointer

    //Assignment operator checks
    r_pl3 = r_pl1;                      //r_pl3.operator=(r_pl1);
    r_pl1 = r_pl3;                      //r_pl1.operator=(r_pl3);
    r_pl3 = r_pl3;
    player1 = player3;                  //Uses the base class assignment
    //player3 = player1;
    player3 = player4;                  //Uses only (!) the derived class assignment if op= specified.
                                        // (!!!) And if op= not specified, uses default RatedPlayer and then op= of the TableTennPlayer
    // r_pl3.showRating();              //Methods of inherited class can't be called neither
    // ptr_pl3->showRating();           //by using a reference nor by using a pointer
/*
    //Dynamic memory allocation
    TableTennPlayer *players[2];        //Create array of pointers to TableTennPlayers

    players[0] = new TableTennPlayer{"Player4", "Man", true};
    players[1] = new RatedPlayer{5, "Player5", "Woman", false};
    delete players[0];
    delete players[1];      //Since the base Destructor is virtual, first call the derived class Destructor, and then the base class's Destructor
*/


    return 0;
}