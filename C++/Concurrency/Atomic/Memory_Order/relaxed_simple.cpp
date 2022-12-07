#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include <assert.h>
#include <unistd.h>

std::atomic<int> x{0};
std::atomic<int> y{0};
std::atomic<int> loadX{0};
std::atomic<int> loadY{0};

/** Sync between three threads **/
// loadX == loadY == 42 i possible:
// although A is sequenced before B within thread 1 and C is sequenced before D within thread 2,
// nothing prevents D from appearing before A in the modification order of y,
// and B from appearing before C in the modification order of x.
// The side effect of D on y could be visible to the load A in thread 1 while the side effect of B on x could be visible to the load C in thread 2.
// In particular, this may occur if D is completed before C in thread 2, either due to compiler reordering or at runtime.
// D -> A -> B -> C gives
void atomics1()
{
    loadY = y.load(std::memory_order_relaxed);      // A
    x.store(loadY, std::memory_order_relaxed);      // B
}

void atomics2()
{
    loadX = x.load(std::memory_order_relaxed);      // C
    y.store(42, std::memory_order_relaxed);         // D
}

int main(int argc, char const *argv[])
{
    std::thread threadOne(atomics1);
    std::thread threadTwo(atomics2);

    threadOne.join();
    threadTwo.join();

    std::cout << "loadX: " << loadX << " loadY: " << loadY << std::endl;

    return 0;
}

