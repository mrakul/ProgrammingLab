#include <iostream>
#include <algorithm>

using namespace std;

// static constexpr int NUM_OF_ELEMENTS = 6;

// template <size_t NUM_OF_ELEMENTS>
// struct distribution
// {
// };

// pair<uint16_t, size_t> &operator=(const pair<uint16_t, size_t> &pairTarget, const uint16_t &uintSource)
// {
// }

int main(int argc, const char **argv) {

    // Distribution test
    uint16_t int_array[] = {10, 30, 10, 30, 20, 30};
    // size_t ints_count[] = {0, 0, 0, 0, 0, 0};

    // std::pair<uint16_t[6], size_t[6]> int_distribution;// = {0, 0 ,0 ,0 ,0 ,0}, {0, 0 ,0 ,0 ,0 ,0};

    std::pair<uint16_t, size_t> int_distribution[6] = {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}};
    // char int_distribution[6] = {0, 0, 0, 0, 0 ,0};

    auto print_int = [](const uint16_t &numToPrint) {std::cout << numToPrint << ' ';};

    // 0. Initial array state
    for_each(int_array, int_array + 6, print_int);
    cout << endl;
    // cout.flush();

    // 1. Sorted array state
    sort(int_array, int_array + 6);
    for_each(int_array, int_array + 6, print_int);
    cout << endl;

    // 2. Unique collapsed
    uint16_t *new_one_past_the_end = unique(int_array, int_array + 6);
    for_each(int_array, new_one_past_the_end, print_int);
    cout << endl;

    // transform(int_array, new_one_past_the_end, ints_count, [](const uint16_t &numToDouble) {return numToDouble * 2;});
    // 3. Fill the distribution
    // copy(int_array, new_one_past_the_end, int_distribution.first);
    transform(int_array, new_one_past_the_end, int_distribution, [&int_array](const uint16_t &curNumToCount)->pair<uint16_t, size_t> {return {curNumToCount, count(int_array, int_array + 6, curNumToCount)};});

    transform(int_array, int_array + 6, int_distribution, [&int_array](const uint16_t &curNumToCount)->pair<uint16_t, size_t> {return {curNumToCount, count(int_array, int_array + 6, curNumToCount)};});

    // 3. Output distribution
    auto print_distribution_item = [](pair<uint16_t, size_t>& pair_item) {cout << pair_item.first << ": " << pair_item.second << endl;};

    for_each(int_distribution, int_distribution + (new_one_past_the_end - int_array), print_distribution_item);
    cout << endl;
    // cout << endl;
    // for_each(int_distribution.second, int_distribution.second + (new_one_past_the_end - int_array), print_int);
    // cout << endl;


// [&int_array](const uint16_t &numToPrint)-> size_t{return count_if(int_array, int_array + 6, numToPrint);
    return EXIT_SUCCESS;
}
