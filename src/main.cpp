#include <iostream>

#include "Ship.hpp"

int main() {
    std::cout << "Ahoy world" << std::endl;

    Ship blackpearl("Black Pearl", 32);
    blackpearl.sail();
    blackpearl.fireCannons();

    return 0;
}