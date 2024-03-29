#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <iostream>

using namespace std;

class Person
{
private:
    int ID;
    string name;
    string surname;
    static int nextID;

public:
    Person();
    Person(const Person &copiedPerson);
    Person(Person &&movedPerson);
    Person(string nameCreate, string surnameCreate);

    Person &operator=(const Person &assignedPerson) = default;                      // Copy assignment operator
    Person &operator=(Person &&movedPerson);                                        // Move assignment operator
    bool operator==(const Person &comparedPerson);
    bool operator<(const Person &comparedPerson) const;                             // Implement it for using in sets. (!) const should be appended

    friend ostream &operator<<(ostream &outStream, const Person &outPerson);
    friend int main(int argc, const char *argv[]);                                  // Make main a friend class to demonstrate partitioning well
    ~Person();
};

// Initialize static data
int Person::nextID = 0;

// Constructors
Person::Person(): ID(nextID++), name("NoName"), surname("NoSurname")
{
    cout << "Default constructor, New object, ID: " << ID << " " << name << " " << surname << endl;
}

Person::Person(const Person &copiedPerson): ID(nextID++), name(copiedPerson.name), surname(copiedPerson.surname)
{
    cout << "Person: Copy Constructor -> New object ID: " << ID << " " << name << " " << surname << endl;
}

Person::Person(Person &&movedPerson) : ID(nextID++)                 // Need not to forget to increment ID (!) in every constructor
{
    // Note: ID is set during creation, so no move it
    // Reminder: move() is not doing anything, just allows to consider movedPerson.name as rvalue, so Move Assignment is applied
    this->name = move(movedPerson.name);
    this->surname = move(movedPerson.surname);
    cout << "Person: Move Constructor -> New object ID: " << ID << " " << name << " " << surname << endl;
}

Person::Person(string nameCreate, string surnameCreate): ID(nextID++), name(nameCreate), surname(surnameCreate)

{
    cout << "Person: (string, string) Constructor -> New object ID: " << ID << " " << name << " " << surname << endl;
}

Person &Person::operator=(Person &&movedPerson)
{
    // Note: ID is set during creation, so no move it
    // Reminder: move() is not doing anything, just allows to consider movedPerson.name as rvalue, so Move Assignment is applied
    this->name = move(movedPerson.name);
    this->surname = move(movedPerson.surname);

    return *this;
}

bool Person::operator==(const Person &comparedPerson)
{
    if (name == comparedPerson.name && surname == comparedPerson.surname)
        return true;
    else
        return false;
}

// Implement less-than operator for using in sets.
bool Person::operator<(const Person &comparedPerson) const
{
    if (surname < comparedPerson.surname)                       // Compare only surnames just for example
        return true;                                            // True => No need to swap items
    else
        return false;                                           // False => Need to swap items
}

ostream &operator<<(ostream &outStream, const Person &outPerson)
{
    cout << "ID: " << outPerson.ID << " " << outPerson.name << " " << outPerson.surname << endl;
    return outStream;
}

Person::~Person()
{
    cout << "Person: Destroyed object ID: " << ID << " " << name << " " << surname << endl;
}


#endif