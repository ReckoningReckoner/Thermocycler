#include<iostream>
#include "CycleTests.h"


int main() {
    std::cout << "Starting Tests\n";
    invalidCycles();
    timedCycles();
    std::cout << "All tests passed!\n";
    return 0;
}
