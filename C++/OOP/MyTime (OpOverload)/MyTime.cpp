#include <iostream>
#include "MyTime.h"

MyTime::MyTime()
{
    hours = 0;
    minutes = 0;
}

MyTime::MyTime(int hrs, int mnts) : hours(hrs), minutes(mnts)
{}

void MyTime::Show() const
{
    std::cout << "It is " << hours << " hours " << minutes << " minutes" << std::endl;
}

void MyTime::AddMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void MyTime::AddHr(int h)
{
    hours += h;
}

void MyTime::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

MyTime MyTime::operator+(const MyTime &added) const
{
    MyTime sum;
    sum.minutes = minutes + added.minutes;
    sum.hours = hours + added.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

MyTime MyTime::operator*(double mult) const
{
    MyTime multObj;
    long totalMins = hours * mult * 60 + minutes * mult;
    multObj.hours = totalMins / 60;
    multObj.minutes = totalMins % 60;
    return multObj;
}

MyTime operator*(double mult, const MyTime &t)    //Friend function: important (!!!) that it has access to the private members of the object
{
    MyTime multObj;
    long totalminutes = t.hours * mult * 60 + t.minutes * mult;
    multObj.hours = totalminutes / 60;
    multObj.minutes = totalminutes % 60;
    return multObj;
}

std::ostream &operator<<(std::ostream &os, const MyTime &t){
    std::cout << "It is " << t.hours << " hours " << t.minutes << " minutes" << std::endl;
    return os; //returns the reference to the object itself
}

//Conversion function
 MyTime::MyTime(double convert){
     minutes = convert;
 }