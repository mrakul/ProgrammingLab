#include <iostream>
#include <array>

const int Size = 5;

template < typename T>
void sum(std::array<double, Size> a, T & fp);

class Adder
{
    double tot;
public:
    Adder(double q = 0) : tot(q) {}
    void operator()(double w) { tot += w; }
    double tot_v() const { return tot; };
};

template<typename T>
void show2(double x, T& funcPtr) { std::cout << x << " -> " << funcPtr(x) << '\n'; }

double f1(double x) { return 1.8 * x + 32; }

int main(int argc, char const *argv[])
{

    //Example 1
    double total = 0.0;
    Adder ad(total);
    std::array<double, Size> temp_c = {32.1, 34.3, 37.8, 35.2, 34.7};
    auto lambFunc = [&total](double added){return total += added;};
    sum(temp_c, lambFunc);
    //total = ad.tot_v();

    std::cout << "total: " << total << '\n';

    //Example 2
    auto funcLamb = [](double x){return 1.8 * x + 32;};
    show2(18.0, funcLamb);

    return 0;
}

template<typename T>
void sum(std::array<double, Size> a, T& fp)
{
    for (auto pt = a.begin(); pt != a.end(); ++pt)
    {
        fp(*pt);
    }
}