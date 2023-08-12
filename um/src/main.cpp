#include <iostream>

#include "communication.h"

int main()
{
    driver* km = new driver;

    //km->procID("cmd.exe");

    std::cout << std::hex << GetCurrentProcessId() << std::endl;
    std::cin.ignore();

    delete km;

    return 0;
}
