#ifndef CELL_H
#define CELL_H

#include <string>
#include <regex>

class Table;

class Cell
{
private:
    int _value;
    bool _isValid = false;

public:
    Cell() = default;
    Cell(int value);

    int getValue() const;
    bool isValid() const;
    std::string toStr() const;
};

#endif // CELL_H
