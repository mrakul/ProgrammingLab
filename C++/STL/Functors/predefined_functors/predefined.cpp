#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>   //to make plus<double> object-functor

using namespace std;

double sqrt (double curVal){
    return curVal * curVal;
}

int main(int argc, char const *argv[])
{
    const int LIM = 5;
    double arr1[LIM] = {4, 7, 10, 2, -6};
    vector<double> doublesVect(arr1, arr1 + LIM);
    vector<double> doublesVect2{1, 2, 3};

    //Make an ostream_iterator to print out
    ostream_iterator<double, char> out(cout, " ");
    //For all values apply sqrt function and copy to out
    transform(doublesVect.begin(), doublesVect.end(), out, sqrt);

    //Paste squares at the end
    transform(doublesVect.begin(), doublesVect.end(), doublesVect.begin(), sqrt);
    cout << "Transformed vector: ";
    for (auto &value : doublesVect)
        cout << value << " ";
    cout << endl;

    //Print out the added values of vectors
    cout << "Sum of vector elements: ";
    transform(doublesVect.begin(), doublesVect.end(), doublesVect2.begin(), out, plus<double>());
    cout << endl;

    //bind1st function test: to multiply on 2.5 every value need to convert binary function to unary by bind1st function
    //Print out multiplied values
    transform(doublesVect.begin(), doublesVect.end(), out, bind1st(multiplies<double>(), 0.5));     //create an anonymous object with binary function and convert to unary

    return 0;
}
