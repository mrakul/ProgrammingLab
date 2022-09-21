#include <iostream>
using namespace std;

template <typename ... Ts>
auto multiplication(Ts ... ts)
{
    return (ts * ... * 1);
}

template <typename ... Ts>
auto addition(Ts ... ts)
{
    return (ts + ... + 0);
}

// Check if values are within the range
template <typename T, typename ... Ts>
bool constexpr within(const T &min, const T &max, const Ts ...ts)
{
    return ((min <= ts && ts <= max) && ...);
}

int main(int argc, char const *argv[])
{
    cout << hex << addition(1, 2, 3, 4, 5, 3.5, 'J') << endl;

    cout << multiplication(1, 2, 3, 4, 5, 3.5) << endl;

    [[maybe_unused]] auto constexpr withinResult = within(10, 20, 1, 15, 30);                      // --> false
    cout << within(10, 20, 11, 12, 13, 15.6f);                     // --> true
    cout << within(5.0, 5.5, 5.1, 5.2, 5.3);                // --> true

    return 0;
}
