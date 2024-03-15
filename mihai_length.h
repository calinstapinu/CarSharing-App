#ifndef mihai_length.h
#define mihai_length.h

#include <string>
#include <stdexcept>
class Length {
private:
    double value;
    std::string unit;

public:
    Length(double val, const std::string& u);
    double get_value() const;
    std::string get_unit() const;
    Length add(const Length& other) const;
    Length subtract(const Length& other) const;
    Length scale(double factor) const;
    Length divide(double divisor) const;
    std::string text() const;
    int compare(const Length& other) const;
};

#endif
