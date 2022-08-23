// lexcast.cpp -- simple cast from float to string
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

int main(int argc, char const* argv[])
{

    using namespace std;
    cout << "Enter your weight: ";
    float weight;
    cin >> weight;

    string resultString = "A 10% increase raises ";
    //Cast float weight to string easily using Boost
    string weightStr = boost::lexical_cast<string>(weight);
    resultString = resultString + weightStr + " to ";           // string operator+()
    weight = 1.1 * weight;
    resultString = resultString + boost::lexical_cast<string>(weight) + ".";
    cout << resultString << endl;

    return 0;
}