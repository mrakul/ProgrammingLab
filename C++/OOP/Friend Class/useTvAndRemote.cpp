#include <iostream>
#include "tv.h"
int main()
{
    using std::cout;
    //Use Tv class public interface
    Tv s42;     //default constructor
    cout << "Initial settings for 42\" TV:\n";
    s42.settings();
    s42.onoff();
    s42.chanup();
    cout << "\nAdjusted settings for 42\" TV:\n";
    s42.settings();

    //Create friend class
    Remote grey;
    grey.set_chan(s42, 10);     //Set the channel directly to 10
    grey.volup(s42);            //Use volup of the Tv class
    grey.volup(s42);            //Use volup of the Tv class
    cout << "\n42\" settings after using remote:\n";
    s42.settings();

    //Another Tv object
    Tv s58(Tv::On);
    s58.set_mode();
    grey.set_chan(s58, 28);
    cout << "\n58\" settings:\n";
    s58.settings();
    return 0;
}