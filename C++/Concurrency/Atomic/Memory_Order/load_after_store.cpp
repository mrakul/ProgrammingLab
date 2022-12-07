#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include <assert.h>
#include <unistd.h>

std::atomic<bool> x{false};
std::atomic<bool> y{false};
std::atomic<bool> loadY{false};
std::atomic<bool> loadX{false};

/** Simple canonical Load after Store example with sequential consistent memory order*/

void store_x_load_y()
{
    x.store(true, std::memory_order_seq_cst);           // SX
    loadY = y.load(std::memory_order_seq_cst);          // LY
}

void store_y_load_x()
{
    y.store(true, std::memory_order_seq_cst);           // SY
    loadX = x.load(std::memory_order_seq_cst);          // LX
}

/*** Explanation */
// There are 4 operations: SX, LY, SY, LX.
//
// X    --> this one can only be Store operation (SX or SY) and can't be one of the Load (LX, LY), since they are arranged relatively
// X    --> Store or Load
// X    --> Store or Load
// X    --> this can be only be Load (LX or LY) and can't be one of the Store (SX or SY)
//
// As a result, we are sure that one of the values will be loaded as changed, because both Stores are guaranteed to be above

int main(int argc, char const *argv[])
{
    std::thread threadOne(store_x_load_y);
    std::thread threadTwo(store_y_load_x);

    threadOne.join();
    threadTwo.join();

    if (loadX == loadY)
        std::cout << "loadX: " << loadX << " loadY: " << loadY << std::endl;

    return 0;
}

