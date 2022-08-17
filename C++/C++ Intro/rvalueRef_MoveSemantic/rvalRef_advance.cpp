#include <cstdlib>
#include <iostream>

using namespace std;

class intsVect
{
public:
    explicit intsVect(string passedName, size_t num = 0) : m_size(num), m_data(new int[m_size]), objName(passedName)
    {
        log("constructor");
    }

    ~intsVect()
    {
        log("destructor");
        if (m_data)
        {
            delete[] m_data;
            m_data = 0;
        }
    }

    intsVect(const intsVect& copiedVect) : m_size(copiedVect.m_size), m_data(new int[m_size]), objName(copiedVect.objName + "_COPY")
    {
        log("copy constructor");
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = copiedVect.m_data[i];
    }

    // In the example below it is used for lvalue of
    intsVect& operator=(intsVect& assignedVect)         //If use non-const reference, will have the message "cannot bind non-const lvalue reference of type 'intsVect&' to an rvalue of type 'intsVect'"" for the rvalue case
                                                        //But for the Temp object 2 this can be used (without const) and use as usual non-const reference
    {
        log("copy assignment operator");
        //intsVect tempVect(assignedVect);            //Make copy based on the input object. tempVect local object is deleted after the operator=() call, it is needed for swap. Or another solution to pass an object by value to create a temporary local object implicitly
        swap(m_size, assignedVect.m_size);              // (!) We can't just use asspignedVect, it is at least const (?), or to use copy by value
        swap(m_data, assignedVect.m_data);
        return *this;
    }

    // Add one more operator=() with rvalue reference
    intsVect& operator=(intsVect&& assignedVect)
    {
        log("move assignment operator");
        std::swap(m_size, assignedVect.m_size);
        std::swap(m_data, assignedVect.m_data);
        return *this;
    }

private:
    void log(const char* msg)
    {
        cout << objName << ": " << "[" << this << "] " << msg << endl;
    }

    size_t m_size;
    int* m_data;
    string objName;     // To output in constructor and destructor
};

int main(int argc, char const* argv[])
{
    cout << "\tStart inner block processing ..." << endl;
    {
        intsVect vector1 = intsVect{"vector1", 3};
        intsVect vector2{"vector2"};

        // Check to assign lvalue
        cout << "assigning lvalue..." << endl;
        vector2 = vector1;
        cout << "ended assigning lvalue..." << endl;

        // Check to assign rvalue
        cout << "assigning rvalue..." << endl;
        // Before adding && rvalue reference, operator=(const intsVect& assignedVect) was called:
        // 1. First, the normal constructor for intsVect "Rvalue temp object" is called to generate the object
        // 2. Second, the assignment operator=() is called, creating another one temporary object "Rvalue temp object_COPY" and copy IT to the vector2
        // 3. Call the destructor for the Rvalue temp object itself
        vector2 = intsVect("Rvalue temp object", 5);

        //But after adding "intsVect& operator=(intsVect&& other)" to have rvalue reference:
        // 1. Normal constructor is called like for the first operator=()
        // 2. New operator=(&&) is called
        // 3. Destructor is called, but no additional object is required
        // The first operator=(&) is used in this case, since vector2 is modifiable lvalue (?)
        intsVect("Temp object 2", 7) = vector2;

        cout << "ended assigning rvalue..." << endl;
    }

    cout << "\tStop inner block processing ..." << endl;
    return 0;
}
