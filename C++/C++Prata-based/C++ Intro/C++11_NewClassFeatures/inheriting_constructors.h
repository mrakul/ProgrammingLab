/*
// Example for function definitions:
class C1
{

public:
    int fn(int j) { ... }
    double fn(double w) { ... }
    void fn(const char* s) { ... }
};

class C2 : public C1
{
public:
    using C1::fn;                   //C1.fn() is available for C2
    double fn(double) { ... };
};

C2 c2;
int k = c2.fn(3);                   // uses C1::fn(int), since it is available for C2
double z = c2.fn(2.4);              // uses C2::fn(double)
*/

//For classes constructors, example:
/*
class BS
{
    int q;
    double w;
public:
    BS() : q(0), w(0) {}
    BS(int k) : q(k), w(100) {}
    BS(double x) : q(-1), w(x) {}
    B0(int k, double x) : q(k), w(x) {}
    void Show() const { std::cout << q << ", " << w << '\n'; }
};

class DR : public BS
{
    short j;
public:
    using BS::BS;                       //Makes BS's constructors available
    DR() : j(-100) {}                   // ! DR needs its own default constructor
    DR(double x) : BS(2 * x), j(int(x)) {}
    DR(int i) : j(-2), BS(i, 0.5 * i) {}
    void Show() const { std::cout << j << ", "; BS::Show(); }
};
int main()
{
    DR o1;                               // use DR()
    DR o2(18.81);                        // use DR(double) instead of BS(double)
    DR o3(10, 1.8);                      // use BS(int, double)
    ...
}
*/