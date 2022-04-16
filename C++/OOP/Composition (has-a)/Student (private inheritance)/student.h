// studentc.h -- defining a Student class using containment
#ifndef STUDENTC_H_
#define STUDENTC_H_
#include <iostream>
#include <string>
#include <valarray>

//Withprivate inheritance, public and protected members of the base class become private members
//of the derived class.This means the methods of the base class do not become part of the public interface of the derived object
class Student : private std::string, private std::valarray<double>  //private inheritance from the classes string and valarray<double>
{
private:
    typedef std::valarray<double> ArrayDb;
    std::ostream &arr_out(std::ostream &os) const;

public:
    // Constructors
    Student() : std::string("Null Student"), ArrayDb() {}
    explicit Student(const std::string &s) : std::string(s), ArrayDb() {}
    explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}

    Student(const std::string &s, int n) : std::string(s), ArrayDb(n) {}
    Student(const std::string &s, const ArrayDb &a) : std::string(s), ArrayDb(a) {}
    Student(const char *str, const double *pd, int n) : std::string(str), ArrayDb(pd, n) {}
    ~Student() {}

    double Average() const;
    const std::string &Name() const;
    double &operator[](int i);
    double operator[](int i) const;
    // Friend functions
    friend std::istream &operator>>(std::istream &is, Student &stu); // 1 word
    friend std::istream &getline(std::istream &is, Student &stu);    // 1 line
    friend std::ostream &operator<<(std::ostream &os, const Student &stu);
};
#endif