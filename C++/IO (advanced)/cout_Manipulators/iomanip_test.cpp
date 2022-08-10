#include <cmath>
#include <iomanip>
#include <iostream>

int main(int argc, char const* argv[]){
    using namespace std;

    // With iomanip, some manupulators may be used in more notantionally
    // convenient form
    cout << fixed << right;

    // Use iomanip manipulators
    cout << setw(6) << "N" << setw(14) << "square root" << setw(15) << "fourth root\n";
    double root;
    for (int n = 10; n <= 100; n += 10){
        root = sqrt(double(n));
        cout << setw(6) << setfill('.') << n << setfill(' ') << setw(12)
            << setprecision(3) << root << setfill('_') << setw(14)
            << setprecision(4) << sqrt(root) << endl;
    }

    return 0;
}