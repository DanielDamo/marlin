#include "Ship.hpp"
#include <iostream>

Ship::Ship(const std::string& name, int cannons)
    : name_(name), cannons_(cannons) {}

void Ship::sail() const {
    std::cout << name_ << " set sail!" << std::endl;
}

void Ship::fireCannons() const {
    std::cout << name_ << " fires " << cannons_ << " cannons!" << std::endl;
}

std::string Ship::getName() const {
    return name_;
}