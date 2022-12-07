#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include <assert.h>
#include <unistd.h>

std::atomic<int> x{0};
std::atomic<int> y{0};
std::atomic<int> loadX1{0};
std::atomic<int> loadX2{0};

void atomics1()
{
    x.store(1, std::memory_order_relaxed);
    x.store(2, std::memory_order_relaxed);
}

void atomics2()
{
    loadX1 = x.load(std::memory_order_relaxed);
    loadX2 = x.load(std::memory_order_relaxed);
}

int main(int argc, char const *argv[])
{
    std::thread threadOne(atomics1);
    std::thread threadTwo(atomics2);

    threadOne.join();
    threadTwo.join();

    std::cout << "loadX: " << loadX1 << " loadY: " << loadX2 << std::endl;

    return 0;
}

