// stock.h -- Stock class interface
#ifndef STOCK_H_
#define STOCK_H_
#include <string>

class Stock // class declaration
{
private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val; } // inline function

public:
    void acquire(const std::string &co, long n, double pr);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show() const;
    //Constructor / Desctructor
    //Stock(); // default constructor
    Stock(int num);
    Stock(const std::string &co = "NoName", long n = 0, double pr = 0.0);
    ~Stock(); // noisy destructor
};
#endif