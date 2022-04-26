// fowl.cpp -- auto_ptr a poor choice
#include <iostream>
#include <string>
#include <memory>
int main()
{
    using namespace std;
    // auto_ptr<string> films[5] =
    //     {
    //         auto_ptr<string>(new string("Fowl Balls")),
    //         auto_ptr<string>(new string("Duck Walks")),
    //         auto_ptr<string>(new string("Chicken Runs")),
    //         auto_ptr<string>(new string("Turkey Errors")),
    //         auto_ptr<string>(new string("Goose Eggs"))};
    // auto_ptr<string> ptrFilm;
    // ptrFilm = films[2];            // films[2] loses ownership => Segmentation fault when using films[2]

    //unique_ptr using
    unique_ptr<string> films[5] =
        {
            unique_ptr<string>(new string("Fowl Balls")),
            unique_ptr<string>(new string("Duck Walks")),
            unique_ptr<string>(new string("Chicken Runs")),
            unique_ptr<string>(new string("Turkey Errors")),
            unique_ptr<string>(new string("Goose Eggs"))};
    unique_ptr<string> ptrFilm;
    //pwin = films[2];                    //compiler prevents this assignment
    cout << "The nominees for best avian baseball film are\n";
    for (int i = 0; i < 5; i++)
        cout << *films[i] << endl;
    cout << "The winner is " << *ptrFilm << "!\n";
    cin.get();

    //shared_ptr using
    shared_ptr<string> films2[5] =
        {
            shared_ptr<string>(new string("Fowl Balls")),
            shared_ptr<string>(new string("Duck Walks")),
            shared_ptr<string>(new string("Chicken Runs")),
            shared_ptr<string>(new string("Turkey Errors")),
            shared_ptr<string>(new string("Goose Eggs"))};
    shared_ptr<string> ptrFilm2;

    ptrFilm2 = films2[4];       //Allowed, both points to the same area, but only the last Destructor will release memory (of the films2)

    return 0;
}