#include <iostream>

#include "communication.h"

int main()
{
    driver* km = new driver;

    std::cout << std::hex << km->procID("cmd.exe") << std::endl;

    std::cin.ignore();

    delete km;

    return 0;
}
