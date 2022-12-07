#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include <assert.h>
#include <unistd.h>

std::atomic<bool> x{false};
std::atomic<bool> y{false};
std::atomic<int> z{0};

// (!!!) Not sure if this example demonstrates the principle appropriately

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst));                 // As I understood, here the thread knows that somewhere x is changed by store()

    if (y.load(std::memory_order_seq_cst)){
       // std::cout << " read x then y\n";
        z++;
    }                      // And here, the thread knows that y is changed elsewhere, so those two loads are not mixed
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));

    if (x.load(std::memory_order_seq_cst)){
        //std::cout << " read y then x\n";
        z++;
    }
}

int main(int argc, char const *argv[])
{
    std::thread threadThree(read_x_then_y);
    std::thread threadFour(read_y_then_x);
    std::thread threadOne(write_x);
    std::thread threadTwo(write_y);

    threadOne.join();
    threadTwo.join();
    threadThree.join();
    threadFour.join();

    //(z == 2) ? (std::cout << "z value is: " << z << std::endl) : (std::cout << "");
    return 0;
}

