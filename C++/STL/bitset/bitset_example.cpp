#include <bitset>   // for std::bitset
#include <iostream>

using namespace std;

//Bitmasks: C++14, all are identical (of course)
constexpr std::uint8_t mask10{ 0b0000'0001 }; // represents bit 0
constexpr std::uint8_t mask11{ 0b0000'0010 }; // represents bit 1
constexpr std::uint8_t mask12{ 0b0000'0100 }; // represents bit 2
constexpr std::uint8_t mask13{ 0b0000'1000 }; // represents bit 3
constexpr std::uint8_t mask14{ 0b0001'0000 }; // represents bit 4
constexpr std::uint8_t mask15{ 0b0010'0000 }; // represents bit 5
constexpr std::uint8_t mask16{ 0b0100'0000 }; // represents bit 6
constexpr std::uint8_t mask17{ 0b1000'0000 }; // represents bit 7

//Bitmasks: C++11, hex representation
constexpr std::uint8_t mask20{ 0x01 }; // hex for 0000 0001
constexpr std::uint8_t mask21{ 0x02 }; // hex for 0000 0010
constexpr std::uint8_t mask22{ 0x04 }; // hex for 0000 0100
constexpr std::uint8_t mask23{ 0x08 }; // hex for 0000 1000
constexpr std::uint8_t mask24{ 0x10 }; // hex for 0001 0000
constexpr std::uint8_t mask25{ 0x20 }; // hex for 0010 0000
constexpr std::uint8_t mask26{ 0x40 }; // hex for 0100 0000
constexpr std::uint8_t mask27{ 0x80 }; // hex for 1000 0000

//Bitmasks: C++11, shift
constexpr std::uint8_t mask30{ 1 << 0 }; // 0000 0001
constexpr std::uint8_t mask31{ 1 << 1 }; // 0000 0010
constexpr std::uint8_t mask32{ 1 << 2 }; // 0000 0100
constexpr std::uint8_t mask33{ 1 << 3 }; // 0000 1000
constexpr std::uint8_t mask34{ 1 << 4 }; // 0001 0000
constexpr std::uint8_t mask35{ 1 << 5 }; // 0010 0000
constexpr std::uint8_t mask36{ 1 << 6 }; // 0100 0000
constexpr std::uint8_t mask37{ 1 << 7 }; // 1000 0000

int main(int argc, char const* argv[])
{
    std::bitset<8> myBitSet{0b0000'0111};     //8 bits in size, binary literal, since C++14, ' - is separator (0x07 or 007)
    std::cout << "Current bitset: " << myBitSet << endl;

    cout << "Number of bits set is: " << myBitSet.count() << endl;
    myBitSet.set(4);
    myBitSet.reset(0);

    std::cout << "Current bitset: " << myBitSet << endl;

    // Shift operators
    myBitSet <<= 1;
    cout << "Move left and OR with 0b0000'1111: " << (myBitSet | std::bitset<8>(0b0000'1111)) << endl;
    std::cout << "Current bitset: " << myBitSet << endl;

    /*** Bitmasks using (without bitset) ***/
    std::uint8_t flags{ 0b0001'0101 }; // 8 bits in size means room for 8 flags, using uint8_t

	std::cout << "bit 0 is " << ((flags & mask10) ? "on" : "off") << endl;
	std::cout << "bit 1 is " << ((flags & mask21) ? "on" : "off") << endl;
	std::cout << "bit 2 is " << ((flags & mask32) ? "on" : "off") << endl;

    //Setting, resetting bits
    flags |= mask21;    //Set the 1st bit (from 0)
    flags &= ~mask30;   //Reset the 0 bit

    cout << "Flags after setting first and resetting the 0 bits: " << static_cast<std::bitset<8>>(flags) << endl;
    cout << "Flags after setting first and resetting the 0 bits: " << std::hex << +flags << endl;   //To print the hex value + may be added before

    /*** Use of bit masks with bitsets ***/
    std::bitset<8> flagSet{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
	std::cout << "bit 1 is " << (flagSet.test(1) ? "on" : "off") << endl;
	std::cout << "bit 2 is " << (flagSet.test(2) ? "on" : "off") << endl;

	flagSet ^= (mask11 | mask12); // flip bits 1 and 2 (use XOR)
	std::cout << "bit 1 is " << (flagSet.test(1) ? "on" : "off") << endl;
	std::cout << "bit 2 is " << (flagSet.test(2) ? "on" : "off") << endl;

	flagSet |= (mask21 | mask22); // turn bits 1 and 2 on
	std::cout << "bit 1 is " << (flagSet.test(1) ? "on" : "off") << endl;
	std::cout << "bit 2 is " << (flagSet.test(2) ? "on" : "off") << endl;

	flagSet &= ~(mask31 | mask32); // turn bits 1 and 2 off
	std::cout << "bit 1 is " << (flagSet.test(1) ? "on" : "off") << endl;
	std::cout << "bit 2 is " << (flagSet.test(2) ? "on" : "off") << endl;

    return 0;
}