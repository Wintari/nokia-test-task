#include "cell.h"
#include "table.h"
#include "errors.h"

Cell::Cell(int value)
{
    _value = value;
    _isValid = true;
}

int Cell::getValue() const
{
    return _value;
}

bool Cell::isValid() const
{
    return _isValid;
}

std::string Cell::toStr() const
{
    if(_isValid)
    {
        return std::to_string(_value);
    }

    return "#ERROR#";
}
