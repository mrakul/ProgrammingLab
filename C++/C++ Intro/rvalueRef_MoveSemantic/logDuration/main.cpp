#include <cstdint>
#include <vector>
#include "LogDuration.h"

using namespace::std;

//Wrapper Vector class
template <typename T>
class Vector {

private:
    vector<T> internalVect;

public:
    Vector(size_t vectSize, T vectValue) : internalVect(vectSize, vectValue) {
    }

    //Copy constructor
    Vector(const Vector& sourceVect) {
        cout << "copy constructor was called\n";
    }

    //Move constructor: in the current example nothing is done, just to demostrate that move constructor is called
    Vector(Vector&& sourceVect){
        cout << "move constructor was called\n";
    }

    size_t size() {return internalVect.size();}
};

int main(int argc, char const *argv[])
{
    //Change to Vector everywhere to demostrate the suitable constructor is used
    vector<uint8_t> sourceVector(1e9, 0);

    {
        LogDuration vectTimeCreation("sourceVector copy1");
        vector<uint8_t> newVector(sourceVector);
    }
    cout << "size of sourceVector is " <<  sourceVector.size() << endl;

    //Track time using move semantics
    {
        LogDuration vectTimeCreation("sourceVector copy2");
        vector<uint8_t> newVector(move(sourceVector));              //No copying the vector one more time, the newVector becomes sourceVector
    }

    //For the case of vector (not Vector) the source vector's size becomes 0
    cout << "size of sourceVector is " <<  sourceVector.size() << endl;
}