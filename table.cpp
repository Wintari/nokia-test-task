#include "table.h"
#include "cell.h"

Table::Table(const std::vector<std::string>& headers)
{
    for(size_t i = 0; i < headers.size(); i++)
    {
        this->_headers.insert({headers[i], i});
        _orderedHeaders.push_back(headers[i]);
    }
}


void Table::setValue(int column, int row, std::string value)
{
    auto innerRowPos = _rowNumbers.find(row);

    if(innerRowPos != _rowNumbers.end())
    {
        int innerRow = innerRowPos->second;
        if((size_t)column < _headers.size())
        {
            Table t({""});
            _cells[innerRow][column] = Cell(*this, value);
        }
    }
}

void Table::setValue(const std::string& column, int row, std::string value)
{
    auto header = _headers.find(column);

    if(header != _headers.end())
    {
        setValue(header->second, row, value);
    }
}

void Table::addRow(int rowNumber, const std::vector<std::string>& values)
{
    if(_rowNumbers.find(rowNumber) == _rowNumbers.end())
    {
        auto cellRow = std::vector<Cell>(_headers.size());
        for(size_t i = 0; i < values.size(); i++)
        {
            cellRow[i] = Cell(*this, values[i]);
        }
        _cells.push_back(cellRow);

        _rowNumbers.insert({rowNumber, _cells.size() - 1});
        _orderedRowNumbers.push_back(rowNumber);
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

std::string Table::getValue(const std::string& column, int row) const
{
    auto header = _headers.find(column);

    if(header != _headers.end())
    {
       return getValue(header->second, row);
    }

    return "";
}

std::string Table::getValue(int column, int row) const
{
    auto innerRowPos = _rowNumbers.find(row);

    if(innerRowPos != _rowNumbers.end())
    {
        int innerRow = innerRowPos->second;
        if((size_t)column < _headers.size())
        {
            if(_cells[innerRow][column].isValid())
            {
                return std::to_string(_cells[innerRow][column].getValue());
            }
            else
            {
                return "#";
            }
        }
    }

    return "";
}
