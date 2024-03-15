#include <iostream>
#include "mihai_length.h"

int main() {
    double val1, val2, scalar;
    std::string unit1, unit2;

    std::cout << "Enter first length value and unit: ";
    std::cin >> val1 >> unit1;
    std::cout << "Enter second length value and unit: ";
    std::cin >> val2 >> unit2;
    std::cout << "Enter a scalar value: ";
    std::cin >> scalar;

    Length len1(val1, unit1);
    Length len2(val2, unit2);

    std::cout << "Length 1: " << len1.text() << std::endl;
    std::cout << "Length 2: " << len2.text() << std::endl;

    try {
        Length added = len1.add(len2);
        std::cout << "Addition result: " << added.text() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        Length subtracted = len1.subtract(len2);
        std::cout << "Subtraction result: " << subtracted.text() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Length scaled = len1.scale(scalar);
    std::cout << "Scaled length 1: " << scaled.text() << std::endl;

    try {
        Length divided = len1.divide(scalar);
        std::cout << "Divided length 1: " << divided.text() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    int comparison = len1.compare(len2);
    if (comparison < 0) {
        std::cout << "Length 1 is smaller than Length 2" << std::endl;
    } else if (comparison > 0) {
        std::cout << "Length 1 is greater than Length 2" << std::endl;
    } else {
        std::cout << "Length 1 is equal to Length 2" << std::endl;
    }

    return 0;
}
