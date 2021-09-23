#ifndef TABLE_H
#define TABLE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <regex>

#include "cell.h"
#include "expressionhandler.h"

class Table
{
private:
    static const std::regex _headerValidator;
    static const std::regex _numberValidator;

    ExpressionHandler _expressionHandler;

    std::unordered_map<std::string, int> _headers;
    std::unordered_map<int, int> _rowNumbers;

    std::vector<std::string> _orderedHeaders;
    std::vector<int> _orderedRowNumbers;

    std::vector<std::vector<Cell>> _cells;

private:
    void setValue(int column, int row, const std::string& value);
    Cell getCell(int column, int row) const;
public:
    Table(const std::vector<std::string>& headers);

    void addRow(const std::string& rowNumberStr, const std::vector<std::string>& values);
    void setValue(const std::string& column, int row, const std::string& value);
    void setValueDirectly(int column, int row, int value);

    const std::vector<std::string>& getHeaders() const;
    const std::vector<int>& getRowNumbers() const;
    const std::vector<Cell>& getRow(int row) const;
    Cell getCell(const std::string& column, int row) const;

    void calculateExpressions();
};

#endif // TABLE_H
