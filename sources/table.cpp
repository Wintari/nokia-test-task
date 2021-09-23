#include "table.h"

#include <algorithm>
#include "utils.h"
#include "errors.h"

const std::regex Table::_headerValidator = std::regex("^\\s*" + cellHeaderRegExp + + "\\s*$");
const std::regex Table::_numberValidator = std::regex("^\\s*" + cellNumberRegExp + + "\\s*$");

Table::Table(const std::vector<std::string>& headers) : _expressionHandler(this)
{
    for(size_t i = 0; i < headers.size(); i++)
    {
        std::string header = headers[i];
        if(std::regex_match(header, _headerValidator))
        {
            header.erase(std::remove_if(header.begin(), header.end(), isspace), header.end());

            this->_headers.insert({header, i});
            _orderedHeaders.push_back(header);
        }
        else
        {
            throw WrongHeaderFormatError;
        }
    }
}


void Table::setValue(int column, int row, const std::string& value)
{
    auto innerRowPos = _rowNumbers.find(row);

    if(innerRowPos != _rowNumbers.end())
    {
        int innerRow = innerRowPos->second;
        if((size_t)column < _headers.size())
        {
            _expressionHandler.handleWhenPossible(innerRow, column, value);
        }
    }
    else
    {
        throw NonexistentRowNumberError;
    }
}

void Table::setValue(const std::string& column, int row, const std::string& value)
{
    auto header = _headers.find(column);

    if(header != _headers.end())
    {
        setValue(header->second, row, value);
    }
    else
    {
        throw NonexistentHeaderError;
    }
}

void Table::setValueDirectly(int column, int row, int value)
{
    if(static_cast<size_t>(column) < _orderedHeaders.size() &&
       static_cast<size_t>(row) < _cells.size())
    {
        _cells[row][column] = Cell(value);
    }
}

void Table::addRow(const std::string& rowNumberStr, const std::vector<std::string>& values)
{
    if(std::regex_match(rowNumberStr, _numberValidator))
    {
        int rowNumber = std::stoi(rowNumberStr);
        if(_rowNumbers.find(rowNumber) == _rowNumbers.end())
        {
            if(values.size() == _orderedHeaders.size())
            {
                _cells.push_back(std::vector<Cell>(values.size()));
                for(size_t i = 0; i < values.size(); i++)
                {
                    _expressionHandler.handleWhenPossible(i, _cells.size() - 1, values[i]);
                }

                _rowNumbers.insert({rowNumber, _cells.size() - 1});
                _orderedRowNumbers.push_back(rowNumber);
            }
            else
            {
                throw WrongRowSizeError;
            }
        }
        else
        {
            throw NonexistentRowNumberError;
        }
    }
    else
    {
        throw WrongRowNumberFormatError;
    }
}

const std::vector<std::string>& Table::getHeaders() const
{
    return _orderedHeaders;
}

const std::vector<int>& Table::getRowNumbers() const
{
    return _orderedRowNumbers;
}

const std::vector<Cell>& Table::getRow(int row) const
{
    auto innerRowPos = _rowNumbers.find(row);

    if(innerRowPos != _rowNumbers.end())
    {
        return _cells[innerRowPos->second];
    }
    else
    {
        throw NonexistentRowNumberError;
    }
}

Cell Table::getCell(const std::string& column, int row) const
{
    auto header = _headers.find(column);

    if(header != _headers.end())
    {
       return getCell(header->second, row);
    }

    else
    {
        throw NonexistentHeaderError;
    }

    return Cell();
}

Cell Table::getCell(int column, int row) const
{
    auto innerRowPos = _rowNumbers.find(row);

    if(innerRowPos != _rowNumbers.end())
    {
        int innerRow = innerRowPos->second;
        if((size_t)column < _headers.size())
        {
            return _cells[innerRow][column];
        }
    }
    else
    {
        throw NonexistentRowNumberError;
    }

    return Cell();
}

void Table::calculateExpressions()
{
    _expressionHandler.handleAll();
}
