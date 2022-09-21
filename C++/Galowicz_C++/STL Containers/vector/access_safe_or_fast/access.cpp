#include <iostream>
#include <vector>
#include <array>
#include <numeric>                  // for std::iota -- filling sequentially from the starting number

int main(int argc, char const *argv[])
{
    constexpr size_t CONTAINER_SIZE{1000};

    /* 1. Example for vector template */
    std::vector<int> intsVect(CONTAINER_SIZE);

    // Fill the vector with rising numbers starting from 0
    std::iota(std::begin(intsVect), std::end(intsVect), 0);

    // Try to access with out of bounds index
    std::cout << "Out of range element value: " << intsVect[CONTAINER_SIZE + 200] << "\n";

    try{
        // This out of bounds access DOES lead to an exception...
        std::cout << "Out of range element value: " << intsVect.at(CONTAINER_SIZE + 10) << "\n";

    }
    catch (const std::out_of_range &outException){
        // ...which we catch here.
        std::cout << "Ooops, out of range access detected: "
            << outException.what() << "\n";
    }


    /* 2. Example for array template */
    std::array<int, CONTAINER_SIZE> intsArray;

    // Fill the array with rising numbers
    std::iota(std::begin(intsArray), std::end(intsArray), 0);

    // Chances are, that the following line will not lead to a crash...
    std::cout << "Out of range element value: " << intsArray[CONTAINER_SIZE + 10] << "\n";

    try{
        // This out of bounds access DOES lead to an exception...
        std::cout << "Out of range element value: " << intsArray.at(CONTAINER_SIZE + 10) << "\n";
    }
    catch (const std::out_of_range &outException){
        // ...which we catch here.
        std::cout << "Ooops, out of range access detected: "
            << outException.what() << "\n";
    }

    return 0;
}