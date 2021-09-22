#include "csvio.h"

#include <string>
#include <vector>
#include "utils.h"

Table CsvReader::readCsvTable(std::istream& stream)
{
    Table table(readHeaders(stream));

    readBody(stream, table);

    return table;
}

std::vector<std::string> CsvReader::readHeaders(std::istream& stream)
{
    std::string headersStr;
    if(std::getline(stream, headersStr))
    {

        auto headers = split(headersStr, ",");
        headers.erase(headers.begin());

        return headers;
    }

    return std::vector<std::string>();
}

void CsvReader::readBody(std::istream& stream, Table& table)
{
    std::string rowStr;
    while(std::getline(stream, rowStr))
    {
        auto row = split(rowStr, ",");

        std::string rowNumber(row.front());

        row.erase(row.begin());

        table.addRow(rowNumber, row);
    }
}

void CsvWriter::writeCsvTable(std::ostream& stream, const Table& table)
{
    writeHeaders(stream, table.getHeaders());

    auto rowNumbers = table.getRowNumbers();
    for(int number : rowNumbers)
    {
        std::vector<std::string> values;
        auto row = table.getRow(number);

        for(const auto& cell : row)
        {
            values.push_back(cell.toStr());
        }

        writeRow(stream, number, values);
    }
}

void CsvWriter::writeHeaders(std::ostream& stream, const std::vector<std::string>& headers)
{
    for(const auto& header : headers)
    {
        stream << "," + header;
    }

    stream << std::endl;
}

void CsvWriter::writeRow(std::ostream& stream, int rowNumber, const std::vector<std::string>& values)
{
    stream << rowNumber;

    for(const auto& value : values)
    {
        stream << "," << value;
    }

    stream << std::endl;;
}
