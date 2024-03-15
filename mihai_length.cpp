#include "mihai_length.h"
Length::Length(double val, const std::string& u) : value(val), unit(u) {}

double Length::get_value() const {
    return value;
}

std::string Length::get_unit() const {
    return unit;
}

Length Length::add(const Length& other) const {
    if (unit == other.unit) {
        return Length(value + other.value, unit);
    } else {
        // Handle incompatible units
        // For simplicity, let's throw an exception
        throw std::runtime_error("Incompatible units for addition");
    }
}

Length Length::subtract(const Length& other) const {
    if (unit == other.unit) {
        return Length(value - other.value, unit);
    } else {
        // Handle incompatible units
        throw std::runtime_error("Incompatible units for subtraction");
    }
}

Length Length::scale(double factor) const {
    return Length(value * factor, unit);
}

Length Length::divide(double divisor) const {
    if (divisor == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Length(value / divisor, unit);
}

std::string Length::text() const {
    return std::to_string(value) + " " + unit;
}

int Length::compare(const Length& other) const {
    if (value < other.value) {
        return -1;
    } else if (value > other.value) {
        return 1;
    } else {
        return 0;


int Length::convert_to(const std::string& target_unit) const {
        if (unit == target_unit) {
            return *this; // No conversion needed
        }

        if (conversionTable.find(unit) == conversionTable.end() ||
            conversionTable.find(target_unit) == conversionTable.end()) {
            throw std::runtime_error("Conversion not supported");
        }

        double factor = conversionTable.at(unit) / conversionTable.at(target_unit);
        return Length(value * factor, target_unit);
    }

}

