#ifndef TABLE_H
#define TABLE_H

#include <unordered_map>
#include <vector>

class Table
{
private:
    std::unordered_map<std::string, int> headers;
    std::unordered_map<int, std::vector<int>> cells;
    std::vector<int> orderedRowNumbers;

    void setValue(int column, int row, int value);
    int getValue(int column, int row) const;
public:
    Table(const std::vector<std::string>& headers);
    void insertRow(int rowNumber, const std::vector<int>& row);
    void addRow(int rowNumber);
    void setValue(const std::string& column, int row, int value);

    std::vector<std::string> getHeaders() const;
    const std::vector<int>& getRowNumbers() const;
    int getValue(const std::string& column, int row) const;
};

#endif // TABLE_H
