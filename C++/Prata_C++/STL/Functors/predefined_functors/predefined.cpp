#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>   //to make plus<double> object-functor

using namespace std;

double sqrt(double curVal)
{
    return curVal * curVal;
}

int main(int argc, char const *argv[])
{
    const int LIM = 5;
    double arr1[LIM] = {4, 7, 10, 2, -6};
    vector<double> doublesVect(arr1, arr1 + LIM);
    vector<double> doublesVect2{1, 2, 3, 0, 0};
    vector<double> doublesVect3;

    // 1. First form of transform() with 4 arguments

    // Make an ostream_iterator to print out
    ostream_iterator<double, char> out(cout, " ");
    cout << "Vector1 initial: " << endl;
    copy(doublesVect.begin(), doublesVect.end(), out);
    cout << endl;
    cout << "Vector2 initial: " << endl;
    copy(doublesVect2.begin(), doublesVect2.end(), out);
    cout << endl;
    // *out++ = '\n';           // doesn't work, since out works with doubles

    // Print out vector1's sqrts (apply sqrt to every vector1 value)
    cout << "Vector1 sqrts -> out: " << endl;
    transform(doublesVect.begin(), doublesVect.end(), out, sqrt);
    cout << endl;
    cout << "Vector1 current: " << endl;
    copy(doublesVect.begin(), doublesVect.end(), out);
    cout << endl;

    // Paste squares at the beginning of the vector2
    // Note: transform doesn't checks the bounds, so need to check if vector2 contains enough elements
    transform(doublesVect.begin(), doublesVect.end(), doublesVect2.begin(), [](const double &curNum){return curNum * curNum;});      // (!) sqrt is unary function here
    // back_inserter(doublesVect3) allows to extend vector during transform
    transform(doublesVect.begin(), doublesVect.end(), std::back_inserter(doublesVect3),[](const decltype(doublesVect3)::value_type &curValue) { return curValue / 2;});

    // Print out vectors' values
    cout << "Vector1 current: " << endl;
    copy(doublesVect.begin(), doublesVect.end(), out);
    cout << endl;
    cout << "Transformed Vector2: " << endl;
    copy(doublesVect2.begin(), doublesVect2.end(), out);
    cout << endl;
    cout << "Transformed Vector3: " << endl;
    copy(doublesVect3.begin(), doublesVect3.end(), out);
    cout << endl;


    // 2. Second form of transform() with 5 arguments: apply plus<double>() binary function for two elements in vectors.
    // Note: transform doesn't checks the bounds!
    cout << "Sum of vector elements: " << endl;
    transform(doublesVect.begin(), doublesVect.end(), doublesVect2.begin(), out, plus<double>());   // plus is binary function, that is takes 2 arguments from both vectors
    cout << endl;

    // count_if() example to count even numbers in the Vector3:
    for (auto &curNum : doublesVect3)
        cout << static_cast<int>(curNum) << " " << endl;
    ptrdiff_t numOfEvenNums = count_if(doublesVect3.begin(), doublesVect3.end(), [](decltype(doublesVect3)::value_type &curValue){return !(static_cast<int>(curValue) & 1);});
    cout << "Num of even numbers (cast to int) in Vector3 is: " << numOfEvenNums << endl;
    // bind1st function test: to multiply on 2.5 every value need to convert binary function to unary by bind1st function
    // Print out multiplied values
    transform(doublesVect.begin(), doublesVect.end(), out, bind1st(multiplies<double>(), 0.5));     //create an anonymous object with binary function and convert to unary

    return 0;
}
