#include "tableTennPlayer.h"
#include "ratedPlayer.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    TableTennPlayer player1 {"Michael", "Pims", true};
    TableTennPlayer player2 {"John", "Lane", false};

    player1.showName();
    player1.HasTable() ? std::cout << "has table " : std::cout << " has no table ";

    player2.showName();
    player2.HasTable() ? std::cout << "has table " : std::cout << " has no table ";

    RatedPlayer player3 {5, player1};   //(!) use constructor with the base object type
    player3.showRating();               // Can be called directly by the object

    //Examples of virtual functions calls
    TableTennPlayer &r_pl1 = player1;
    TableTennPlayer &r_pl3 = player3;
    TableTennPlayer * ptr_pl3 = &player3;       //By pointer

    r_pl1.showName();
    r_pl3.showName();                   //Call overloaded function (since it it virtual)
    // r_pl3.showRating();              //Methods of inherited class can't be called neither
    // ptr_pl3->showRating();           //by using a reference nor by using a pointer

    //Dynamic memory allocation
    TableTennPlayer *ptr_pl4 = new TableTennPlayer{"Player4", "Man", true};
    TableTennPlayer *ptr_pl5 = new RatedPlayer{5, "Player5", "Woman", false};
    delete ptr_pl4;
    delete ptr_pl5;

    return 0;
}
