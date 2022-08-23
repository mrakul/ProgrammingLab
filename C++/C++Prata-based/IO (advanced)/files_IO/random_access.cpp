#include <iostream> // not required by most systems
#include <fstream>
#include <iomanip>
#include <cstdlib> // for exit()

const int LIM = 20;

//#pragma pack(push, 1) The size of the planetData without pragma pack is 40, and with it - 36. Alignment f 4 symbols after name(?)

struct planetData
{
    char name[LIM]; // name of planet
    double population; // its population
    double gravity; // its acceleration of gravity
};

const char* file = "planets.dat";   // Assumed to be populated already

inline void eatline() {
    while (std::cin.get() != '\n') continue; }  //Read char-by-char to identify NewLine

void printBuffPos(std::fstream &strToOut);    //To print out the buffer current positions

int main(int argc, char const* argv[])
{
    using namespace std;
    planetData curPlanet;
    cout << fixed;          // Use fixed-point notation.

    // 1. Print out the initial content
    fstream fStreamInOut;     // Create read and write stream (sterams?), that is two buffers for input and output
    fStreamInOut.open(file, ios_base::in | ios_base::out | ios_base::binary);     //Open file in binary IN/OUT mode
    int planetsCnt = 0;

    if (fStreamInOut.is_open())
    {
        fStreamInOut.seekg(0);    // Set to the beginning
        cout << "Here are the current content of the " << file << " file:" << endl;
        while (fStreamInOut.read(reinterpret_cast<char*>(&curPlanet), sizeof(curPlanet)))        // Important that need to cast to (char *) the structure's address
        {
            cout << planetsCnt++ << ": " << setw(LIM) << curPlanet.name << ": "
                << setprecision(0) << setw(12) << curPlanet.population
                << setprecision(2) << setw(6) << curPlanet.gravity << endl;
        }
        // If successful read, reset the flags. Otherwise, exit from the program
        if (fStreamInOut.eof())
            fStreamInOut.clear(); // clear eof flag
        else
        {
            cerr << "Error in reading " << file << '.' << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cerr << file << " could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    // 2. Read the record of the specified number and change the record of the specified number
    cout << "Enter the record number you wish to change: ";
    long recNum;
    cin >> recNum;
    eatline(); // get rid of newline

    if (recNum < 0 || recNum >= planetsCnt)
    {
        cerr << "Invalid record number, reinput, please" << endl;
        exit(EXIT_FAILURE);
    }

    streampos recPos = recNum * sizeof(curPlanet);  // convert to streampos type
    printBuffPos(fStreamInOut);     // Print out buffer positions before navigating
    fStreamInOut.seekg(recPos);       // Navigate to the required record position in the read buffer
    if (fStreamInOut.fail())
    {
        cerr << "Error on attempted seek" << endl;
        exit(EXIT_FAILURE);
    }

    // Read the specified record
    printBuffPos(fStreamInOut);     // Print out buffer positions before reading
    fStreamInOut.read(reinterpret_cast<char *>(&curPlanet), sizeof(curPlanet));
    cout << "Your selection:" << endl;
    cout << recNum << ": " << setw(LIM) << curPlanet.name << ": "
        << setprecision(0) << setw(12) << curPlanet.population
        << setprecision(2) << setw(6) << curPlanet.gravity << endl;
    if (fStreamInOut.eof())
        fStreamInOut.clear(); // clear eof flag

    printBuffPos(fStreamInOut);     // Print out buffer positions after reading

    // Input the new planet's data
    cout << "Enter planet name: ";
    cin.get(curPlanet.name, LIM);       // cin.get() leaves the NewLine in the buffer
    eatline();
    cout << "Enter planetary population: ";
    cin >> curPlanet.population;        // >> extraction discards the whitespace characters(?), so no need to discard it manually
    cout << "Enter planet's acceleration of gravity: ";
    cin >> curPlanet.gravity;

    fStreamInOut.seekp(recPos);   // (!) Return at the beginning of the record, since reading moved the pointers (both??) after the record
    printBuffPos(fStreamInOut);     // Print out buffer positions after navigating to the required record, before writing

    fStreamInOut.write((char*)&curPlanet, sizeof(curPlanet)) << flush;        // Needed to be sure that the buffer is flushed (so the file is updated) before making the next step
    printBuffPos(fStreamInOut);     // Print out buffer positions after writing
    if (fStreamInOut.fail())
    {
        cerr << "Error on attempted write" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Read buffer position is: " << fStreamInOut.tellg() << "Write buffer position is: " << fStreamInOut.tellp() << endl;

    // 3. Print out the file with the changed record
    planetsCnt = 0;
    fStreamInOut.seekg(0); // go to beginning of file
    printBuffPos(fStreamInOut);     // Print out buffer positions after rewinding back
    cout << "Here are the new contents of the " << file
        << " file:" << endl;
    while (fStreamInOut.read((char*)&curPlanet, sizeof(curPlanet)))
    {

        cout << planetsCnt++ << ": " << setw(LIM) << curPlanet.name << ": "
            << setprecision(0) << setw(12) << curPlanet.population
            << setprecision(2) << setw(6) << curPlanet.gravity << endl;
        printBuffPos(fStreamInOut);     // Print out buffer positions after reading the record
    }

    fStreamInOut.close();
    cout << "Done." << endl;
    return 0;
}

void printBuffPos(std::fstream &strToOut){
    std::cout << "Read buffer position is: " << strToOut.tellg() << " Write buffer position is: " << strToOut.tellp() << std::endl;
}