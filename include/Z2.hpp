#pragma once

#include <iostream>
#include <stdexcept>

struct Z2 {
    int value;
    int order = 2;

    Z2(int v = 1) {
        if (v == -1 || v == 1) {
            value = v;
        } else {
            std::cerr << "Invalid value. Z2 can only have -1 or 1." << std::endl;
            value = 1;  
        }
    }

    void display() const {
        std::cout << "Value in Z2: " << value << std::endl;
    }

    bool operator==(const Z2& other) const {
        return value == other.value;
    }

    Z2 operator*(const Z2& other) const {
        return Z2(value * other.value);
    }
};