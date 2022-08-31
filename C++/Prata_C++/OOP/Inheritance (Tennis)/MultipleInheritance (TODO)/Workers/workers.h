// workermi.h -- working classes with MI
#ifndef WORKERMI_H_
#define WORKERMI_H_
#include <string>
class Worker // an abstract base class
{
private:
    std::string fullname;
    long id;

protected:
    virtual void Data() const;
    virtual void Get();

public:
    Worker() : fullname("no one"), id(0L) {}
    Worker(const std::string &s, long n)
        : fullname(s), id(n) {}
    virtual ~Worker() = 0; // pure virtual function
    virtual void Set() = 0;
    virtual void Show() const = 0;
};

class Waiter : virtual public Worker        //Make base class virtual not to inherit it twice by SingingWater
{
private:
    int panache;

protected:
    void Data() const;
    void Get();

public:
    Waiter() : Worker(), panache(0) {}
    Waiter(const std::string &s, long n, int p = 0)
        : Worker(s, n), panache(p) {}
    Waiter(const Worker &wk, int p = 0)
        : Worker(wk), panache(p) {}
    void Set();
    void Show() const;
};

class Singer : virtual public Worker    //Make base class virtual not to inherit it twice by SingingWater
{
protected:
    enum
    {   other, alto,
        contralto, soprano,
        bass, baritone, tenor
    };
    enum { Vtypes = 7 };
    void Data() const;
    void Get();

private:
    static const char *pv[Vtypes]; // string equivs of voice types
    int voice;

public:
    Singer() : Worker(), voice(other) {}
    Singer(const std::string &s, long n, int v = other)
        : Worker(s, n), voice(v) {}
    Singer(const Worker &wk, int v = other)
        : Worker(wk), voice(v) {}
    void Set();
    void Show() const;
};

// multiple inheritance
class SingingWaiter : public Singer, public Waiter
{
protected:
    void Data() const;
    void Get();

public:

    //Constructors
    // (!) Constructors uses Worker(wk) constructors explicitly not to have ambiguity of
    // several paths of Singer and Waiter;
    // If not use explicitly Worker, then default will be used
    SingingWaiter() {}
    SingingWaiter(const std::string &s, long n, int p = 0,
                  int v = other) : Worker(s, n), Singer(s, n, v), Waiter(s, n, p) {}
    SingingWaiter(const Worker &wk, int p = 0, int v = other)
        : Worker(wk), Singer(wk, v), Waiter(wk, p) {}
    SingingWaiter(const Waiter &wt, int v = other)
        : Worker(wt), Singer(wt, v), Waiter(wt) {}
    SingingWaiter(const Singer &wt, int p = 0)
        : Worker(wt), Singer(wt), Waiter(wt, p) {}
    void Set();
    void Show() const;
};
#endif