#pragma once
#include <string>

class Ship{
    public:
        Ship(const std::string& name, int cannons);
        void sail() const;
        void fireCannons() const;

        std::string getName() const;

    private:
        std::string name_;
        int cannons_;
};