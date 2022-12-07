#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include <assert.h>
#include <unistd.h>

std::atomic<int> x{0};
std::atomic<int> y{0};

/** Sync between three threads **/
// 1. memory_order_seq_cst:
// With this memory order it is guaranteed that no asserts will be failed.
// Other threads are aware of another, for the example below, threads2 and threads3 knows that X and Y are changed by the thread1 (my understanding)

// 2. memory_order_relaxed
// With this memory order both asserts may be failed (explanation from GCC)
// Note: my understanding is that other threads (2 and 3) are not aware of the rest (thread1), this way the conditions can be optimized

void atomics1()
{
    y.store(20, std::memory_order_seq_cst);           // SY: with Seq memory order, Y is guaranteed to be changed before X
    x.store(10, std::memory_order_seq_cst);           // SX: if X is changed before Y (for Relaxed case), then thread2's condition will be passed
}

void atomics2()
{
    if (x.load(std::memory_order_seq_cst) == 10){           // LX: with Relaxed order, threads don't know about thread1's SX and SY, so the code may be optimized (my understanding)
        assert(y.load(std::memory_order_seq_cst) == 20);    // If SY from thread1 not processed, this assert may fail
        y.store(10, std::memory_order_seq_cst);             // (?) for Relaxed case, code may be optimized and this SY may be processed before SX(10) of the thread1
    }
}

void atomics3()
{
    if (y.load(std::memory_order_seq_cst) == 10){           // If SY(10) of the thread2 is processed before SX(10) of the first thread, then assert below may be failed
        assert(x.load(std::memory_order_seq_cst) == 10);    // SX of the thread1 is not processed
    }
}

int main(int argc, char const *argv[])
{
    std::thread threadOne(atomics1);
    std::thread threadTwo(atomics2);
    std::thread threadThree(atomics3);

    threadOne.join();
    threadTwo.join();
    threadThree.join();

    std::cout << "X: " << x << " Y: " << y << std::endl;
    // if (loadX == loadY)
    //     std::cout << "loadX: " << loadX << " loadY: " << loadY << std::endl;

    return 0;
}

