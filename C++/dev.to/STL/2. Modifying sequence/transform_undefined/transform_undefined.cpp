#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Number
{
private:
    int numValue;

public:
    Number(){
        cout << "Empty constructor " << "\n";
    }

    Number(const Number &copiedNumber): numValue(copiedNumber.getNumber()){
        cout << "Copy constructor with numValue: " << copiedNumber.getNumber() << "\n";
    }

    Number(int numInitValue): numValue(numInitValue){
        cout << "Default constructor with value: " << numInitValue << "\n";
    }

    ~Number(){
        cout << "Destructor " << numValue << "\n";
    }

    int getNumber() const { return numValue; }
};

int main(int argc, char const *argv[])
{
    // 0. Create the large first vector and smaller second to demonstrate that we will be out of region when going through the second container, or even have Segmentation Fault when the first container is large enough
    vector<Number> sourceVector1(5, Number{7});                                                 //(2000000, Number{7} => two billions are enough to give Segmentation Fault :)
    vector<Number> sourceVector2{Number{10}, Number{20}, Number{30}};
    cout << sourceVector1.size() << '/' << sourceVector1.capacity() << endl;
    cout << sourceVector2.size() << '/' << sourceVector2.capacity() << endl;
    vector<int> resultVector{};

    // 1. Use the second variation of transform() to output to the third container (resultVector)
    transform(sourceVector1.begin(), sourceVector1.end(), sourceVector2.begin(), back_inserter(resultVector), [](Number curItem1, Number curItem2) {return curItem1.getNumber() + curItem2.getNumber();});
    for_each(resultVector.begin(), resultVector.end(), [](int curItem){ cout << curItem << "\n";});

    return 0;
}
