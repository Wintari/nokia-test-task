#include "cell.h"
#include "utils.h"
#include "table.h"

const std::regex Cell::intValidator = std::regex("^\\s*" + intRegExp + + "\\s*$");
const std::regex Cell::expressionValidator = std::regex("^\\s*=" + argumentRegExp + operatorRegExp +
                                                        argumentRegExp + "\\s*$");

Cell::Cell(const Table& table, const std::string& value)
{

    if(std::regex_match(value, intValidator))
    {
        _value = std::stoi(value);
        _isValid = true;
    }
    else if(std::regex_match(value, expressionValidator))
    {
        _isValid = false;
    }
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
