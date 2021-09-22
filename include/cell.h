#ifndef CELL_H
#define CELL_H

#include <string>
#include <regex>

class Table;

class Cell
{
private:
    static const std::regex intValidator;
    static const std::regex expressionValidator;

    int _value;
    bool _isValid = false;

public:
    Cell() = default;
    Cell(const Table& table, const std::string& value);

    int getValue() const;
    bool isValid() const;
    std::string toStr() const;
};

#endif // CELL_H
