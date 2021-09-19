#include "table.h"
#include <string>

Table::Table(const std::vector<std::string>& headers)
{
    for(size_t i = 0; i < headers.size(); i++)
    {
        this->headers.insert({headers[i], i});
    }
}

void Table::insertRow(int rowNumber, const std::vector<int>& row)
{
    if(row.size() == headers.size())
    {
        addRow(rowNumber);
        auto rowCells = cells.find(rowNumber);

        for(size_t i = 0; i < row.size(); i++)
        {
            rowCells->second[i] = row[i];
        }

        orderedRowNumbers.push_back(rowNumber);
    }
}

void Table::setValue(int column, int row, int value)
{
    auto rowCells = cells.find(row);

    if(rowCells != cells.end())
    {
        if((size_t)column < rowCells->second.size())
        {
            rowCells->second[column] = value;
        }
    }
}

void Table::setValue(const std::string& column, int row, int value)
{
    auto header = headers.find(column);

    if(header != headers.end())
    {
        setValue(header->second, row, value);
    }
}

void Table::addRow(int rowNumber)
{
    cells.insert({rowNumber, std::vector<int>(headers.size())});
}

std::vector<std::string> Table::getHeaders() const
{
    std::vector<std::string> convertedHeaders(headers.size());

    for(const auto& header : headers)
    {
        convertedHeaders[header.second] = header.first;
    }

    return convertedHeaders;
}

const std::vector<int>& Table::getRowNumbers() const
{
    return orderedRowNumbers;
}

int Table::getValue(const std::string& column, int row) const
{
    auto header = headers.find(column);

    if(header != headers.end())
    {
       return getValue(header->second, row);
    }
}

int Table::getValue(int column, int row) const
{
    auto rowCells = cells.find(row);

    if(rowCells != cells.end())
    {
        if((size_t)column < rowCells->second.size())
        {
            return rowCells->second[column];
        }
    }
}
