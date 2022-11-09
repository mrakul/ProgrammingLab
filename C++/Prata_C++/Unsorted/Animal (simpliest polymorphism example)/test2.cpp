#include <iostream>
#include <string>
using namespace std;

class Animal
{
private:
    string type;

public:
    // constructor to initialize type
    Animal() : type("Animal") {}

    // declare virtual function
    string getType()
    {
        return type;
    }
};

class Dog : public Animal
{
private:
    string type;

public:
    // constructor to initialize type

    using Animal::getType;
    Dog() : type("Dog") {}

    string getType(int a)
    {
        cout << "Dog's getType()" << endl;
        return type;
    }

};

class Cat : public Animal
{
private:
    string type;

public:
    // constructor to initialize type
    Cat() : type("Cat") {}

    string getType()
    {
        cout << "Cat's getType()" << endl;
        return type;
    }
};

void print(Animal *ani)
{
    cout << "Animal: " << ani->getType() << endl;
}

int main()
{
    Animal *animal1 = new Animal();
    Dog *dog1 = new Dog();
    Cat *cat1 = new Cat();

    cout << animal1->getType() << endl;
    cout << dog1->getType() << endl;
    cout << cat1->getType() << endl;


    print(animal1);
    print(dog1);
    print(cat1);

    return 0;
}