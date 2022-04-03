#ifndef MYTIME_H_
#define MYTIME_H_
#include <iostream>

class MyTime
{
private:
    int hours;
    int minutes;
    static const int a = 0;

public:
    MyTime();
    MyTime(int hrs, int mnts = 0);
    //MyTime(double convert); //to convert from double to MyTime, actually constructor?
    // Or this way not to make implicit conversion, only with MyTime() constructor name
    explicit MyTime(double convert); //to convert from double to MyTime:

    void Show() const;
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h, int m);
    MyTime operator+(const MyTime &added) const;
    MyTime operator*(double mult) const;
    friend MyTime operator*(double mult, const MyTime &t);
    friend std::ostream &operator<<(std::ostream &os, const MyTime &t);

    //Conversion functions
    operator double();  //to convert MyTime to double
};

#endif
