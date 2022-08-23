// binary.cpp -- binary file I/O
#include <iostream> // not required by most systems
#include <fstream>
#include <iomanip>
#include <cstdlib> // for exit()

inline void eatline() { while (std::cin.get() != '\n') continue; }

struct planetData
{
    char name[20]; // name of planet
    double population; // its population
    double gravity; // its acceleration of gravity
};

const char* file = "planets.dat";

int main(int argc, char const *argv[])
{
    using namespace std;
    planetData curPlanet;
    cout << fixed << right;

    // 1. Print out the initial data of the file
    ifstream fin;
    fin.open(file, ios_base::in | ios_base::binary | ios_base::app); // binary file
    //NOTE: some systems don't accept the ios_base::binary mode
    if (fin.is_open())
    {
        cout << "Here are the current contents of the "
            << file << " file:" << endl;
        while (fin.read((char*)&curPlanet, sizeof(curPlanet)))
        {
            cout << setw(20) << curPlanet.name << ": "
                << setprecision(0) << setw(12) << curPlanet.population
                << setprecision(2) << setw(6) << curPlanet.gravity << endl;
        }
        fin.close();
    }

    // 2. Add new data
    ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);
    //NOTE: some systems don't accept the ios::binary mode
    if (!fout.is_open())
    {
        cerr << "Can't open " << file << " file for output:" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Enter planet name (enter a blank line to quit): ";
    cin.get(curPlanet.name, 20);
    while (curPlanet.name[0] != '\0')  //If blank line is inputted
    {
        eatline();
        cout << "Enter planetary population: ";
        cin >> curPlanet.population;
        cout << "Enter planet's acceleration of gravity: ";
        cin >> curPlanet.gravity;
        eatline();
        fout.write((char*)&curPlanet, sizeof(curPlanet));       // (!!!) Important that we are writing the entire field of its size, not only the length of the actual data
        cout << "Enter planet name (enter a blank line to quit):" << endl;
        cin.get(curPlanet.name, 20);
    }

    fout.close();

    // 3. Print out the renewed file
    fin.clear(); // not required for some implementations, but won't hurt
    fin.open(file, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        cout << "Here are the new contents of the "
            << file << " file:" << endl;
        while (fin.read((char*)&curPlanet, sizeof curPlanet))
        {
            cout << setw(20) << curPlanet.name << ": "
                << setprecision(0) << setw(12) << curPlanet.population
                << setprecision(2) << setw(6) << curPlanet.gravity << endl;
        }
        fin.close();
    }
    cout << "Done." << endl;

    return 0;
}