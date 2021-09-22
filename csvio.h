#ifndef CSVIO_H
#define CSVIO_H

#include <iostream>
#include "table.h"

class CsvReader
{
private:
    std::vector<std::string> readHeaders(std::istream& stream);
    void readBody(std::istream& stream, Table& table);
public:
    Table readCsvTable(std::istream& stream);
};

class CsvWriter
{
private:
    void writeHeaders(std::ostream& stream, const std::vector<std::string>& headers);
    void writeRow(std::ostream& stream, int rowNumber, const std::vector<std::string>& values);
public:
    void writeCsvTable(std::ostream& stream, const Table& table);
};

Table readCsvTable(std::istream& stream);

#endif // CSVIO_H
