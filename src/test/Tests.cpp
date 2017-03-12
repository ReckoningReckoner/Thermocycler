#include<iostream>
#include "CycleTests.h"


int main() {
    std::cout << "Starting Tests\n------------\n";
    invalidCycles();
    timedCycles();
    interfaceTests();
    std::cout << "All tests passed!\n-----------\n";
    return 0;
}
