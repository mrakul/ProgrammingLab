#include <cmath>
#include <iostream>
#include <chrono>

// using namespace std;

int main(int argc, char **argv) {

    int a;
    std::cout << std::exp(2) << " " << std::exp(700) << " " << std::exp(710) << " " << std::exp(-730) << std::endl;

    float infinity = -std::numeric_limits<double>::infinity();

    std::cout << infinity << std::endl;

    std::cout << "2^4: " <<  std::pow(2, 4) << std::endl;

    // Measurement std::exp2
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto exp2 = std::exp(2);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "exp2" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    // Measurement std::exp100
    begin = std::chrono::steady_clock::now();
    auto exp100 = std::exp(100);
    end = std::chrono::steady_clock::now();

    std::cout << "exp100" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    // Measurement std::exp700
    begin = std::chrono::steady_clock::now();
    auto exp700 = std::exp(700);
    end = std::chrono::steady_clock::now();

    std::cout << "exp700" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    // Measurement pow3_2
    begin = std::chrono::steady_clock::now();
    auto pow3_5 =  std::pow(3, 2);
    end = std::chrono::steady_clock::now();

    std::cout << "pow3_2" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    // Measurement pow3_20
    begin = std::chrono::steady_clock::now();
    auto pow3_20 =  std::pow(3, 20);
    end = std::chrono::steady_clock::now();

    std::cout << "pow3_20" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    // Measurement pow3_25
    begin = std::chrono::steady_clock::now();
    auto pow3_25 =  std::pow(3, 128);
    end = std::chrono::steady_clock::now();

    std::cout << "pow3_25" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    return EXIT_SUCCESS;
}