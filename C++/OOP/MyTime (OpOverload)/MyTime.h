#ifndef MYTIME_H_
#define MYTIME_H_
#include <iostream>

class MyTime
{
private:
    int hours;
    int minutes;
    //int c{3};
    static const int a;// = 5; //Constant may be initizalized within the class definition, or in MyTime.cpp as static int
    static int b;           //Initialized in the MyTime.cpp

public:
    MyTime();
    explicit MyTime(int hrs, int mnts = 0);
    //MyTime(double convert); //to convert from double to MyTime, actually constructor?
    // Or this way not to make implicit conversion, only with MyTime() constructor name
    explicit MyTime(double convert); //to convert from double to MyTime: (!) 'explicit' keyword means that no conversion will occur implicitly

    void Show() const;
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h, int m);
    MyTime operator+(const MyTime &added) const;
    MyTime operator*(double mult) const;
    friend MyTime operator*(const double mult, const MyTime &t);
    friend std::ostream &operator<<(std::ostream &os, const MyTime &t);

    //Conversion functions
    operator double();  //to convert MyTime to double
};

#endif
