#include <iostream>
#include "table.h"

using namespace std;

int main()
{
    Table table({"a", "b", "c"});
    table.insertRow(1, {1, 2, 3});
    table.insertRow(10, {4, 5, 6});
    table.insertRow(5, {7, 8, 9});

    table.setValue("b", 10, 35);

    auto headers = table.getHeaders();
    auto rowNumbers = table.getRowNumbers();

    auto value = table.getValue(headers[1], rowNumbers[1]);

    return 0;
}
