#include <stdio.h>
// 7 -> 3
// 8 -> 1
// 16 -> 1
// 0 -> 0
int count_ones(int val);

int main(int argc, char const *argv[]){

    // Check the result
    printf("Num of set bits of %d is %d\n", 7, count_ones(7));
    printf("Num of set bits of %d is %d\n", 8, count_ones(8));
    printf("Num of set bits of %d is %d\n", 16, count_ones(16));
    printf("Num of set bits of %d is %d\n", 0, count_ones(0));

    return 0;
}

int count_ones(int val)
{
    int curBitToCheck = 0x00000001;
    int numOfSetBits = 0;

    for (int i = 0; i < sizeof(val) * 8; i++){            // Surely, need to consider number of bits in a byte
        if (val & curBitToCheck)
            ++numOfSetBits;
        curBitToCheck = curBitToCheck << 1;
    }

    return numOfSetBits;
}
