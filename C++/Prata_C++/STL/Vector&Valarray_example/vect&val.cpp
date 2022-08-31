// Comparing vector and valarray
#include <iostream>
#include <valarray>
#include <vector>
#include <algorithm>
int main(int argc, char const *argv[])
{
    using namespace std;
    vector<double> vectorNumbers;
    double dblValue;

    //Populate the vector by numbers
    cout << "Enter numbers (<=0 to quit):\n";
    while (cin >> dblValue && dblValue > 0)
        vectorNumbers.push_back(dblValue);
    //Sort vector values in ascending order
    sort(vectorNumbers.begin(), vectorNumbers.end());

    //Create valarray of the same size and populate with the same values of the vector
    int vectSize = vectorNumbers.size();
    valarray<double> valarrNumbers(vectSize);
    //Note: can't use the copy() function, because valarray has no iterators
    for (int i = 0; i < vectSize; i++)
        valarrNumbers[i] = vectorNumbers[i];

    //Create another one valarray having the vector's size
    valarray<double> valarrSqrt(vectSize);
    valarrSqrt = sqrt(valarrNumbers);       //apply the function to every element of the valarrNumbers

    //Create another one array
    valarray<double> results(vectSize);
    results = valarrNumbers + 2.0 * valarrSqrt;
    cout.setf(ios_base::fixed);
    cout.precision(2);

    for (int i = 0; i < vectSize; i++)
    {
        cout.width(20);
        cout << "Function result for " <<valarrNumbers[i] << " is: ";
        cout.width(8);
        cout << results[i] << endl;
    }

    return 0;
}