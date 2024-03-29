// stock00.cpp -- implementing the Stock class
#include <iostream>
#include "stock.h"

void Stock::acquire(const std::string &co, long n, double pr)
{
    company = co;
    if (n < 0)
    {
        std::cout << "Number of shares can’t be negative; "
                  << company << " shares set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}

void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        std::cout << "Number of shares purchased can’t be negative. "
                  << "Transaction is aborted.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if (num < 0)
    {
        cout << "Number of shares sold can’t be negative. "
             << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        cout << "You can’t sell more than you have! "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}
void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show() const
{
    using std::cout;
    using std::endl;
    using std::ios_base;
    // set format to #.###
    ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
    std::streamsize prec = cout.precision(3);
    cout << "Company: " << company << " Shares: " << shares << endl;
    cout << " Share Price: $" << share_val;
    // set format to #.##
    cout.precision(2);
    cout << " Total Worth: $" << total_val << endl;
    // restore original format
    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}

const Stock &Stock::compare(const Stock &st) const{
    if (st.total_val >= this->total_val)
        return st;
    else
        return *this;
}
// Constructor definitions

//Only one default constructor may exist
Stock::Stock()
{
    company = "NoName";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
    std::cout << "Object created!";
}

Stock::Stock(const std::string &companyName, long n, double pr){
    company = companyName;
    if (n < 0)
    {
        std::cerr << "Number of shares cannot be negative; "
                  << company << " shares set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
    std::cout << company << ": Object created! " << std::endl;
}

//Constructor with one formal parameter and use of list of initialization (recommended?)
Stock::Stock(int num) : share_val(num){}

Stock::~Stock() // class destructor
{
    std::cout << "Bye, " << company << "\n";
}