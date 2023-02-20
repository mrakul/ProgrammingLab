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
    Person(string nameCreate, string surnameCreate);

    Person &operator=(const Person &assignedPerson) = default;                      // Copy assignment operator
    Person &operator=(Person &&movedPerson);                                        // Move assignment operator
    bool operator==(const Person &comparedPerson);

    friend ostream &operator<<(ostream &outStream, const Person &outPerson);
    ~Person();
};

// Initialize static data
int Person::nextID = 0;

Person::Person() : ID(nextID++), name("NoName"), surname("NoSurname")
{
    cout << "Default constructor, New object, ID: " << ID << " " << name << " " << surname << endl;
}

Person::Person(const Person &copiedPerson) : ID(nextID++), name(copiedPerson.name), surname(copiedPerson.surname){
    cout << "Person: Copy Constructor -> New object ID: " << ID << " " << name << " " << surname << endl;
}

Person::Person(string nameCreate, string surnameCreate) : ID(nextID++), name(nameCreate), surname(surnameCreate)
{
    cout << "Person: (string, string) Constructor -> New object ID: " << ID << " " << name << " " << surname << endl;
}

ostream &operator<<(ostream &outStream, const Person &outPerson){
    cout << "ID: " << outPerson.ID << " " << outPerson.name << " " << outPerson.surname << endl;
    return outStream;
}

Person &Person::operator=(Person &&movedPerson){
    // Note: ID is set during creation, so no move it
    this->name = move(movedPerson.name);
    this->surname = move(movedPerson.surname);

    return *this;
}

Person::~Person()
{
    cout << "Person: Destroyed object ID: " << ID << " " << name << " " << surname << endl;
}

bool Person::operator==(const Person &comparedPerson){
    if (name == comparedPerson.name && surname == comparedPerson.surname)
        return true;
    else
        return false;
}

#endif