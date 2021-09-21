#include <iostream>
#include "table.h"
#include "cell.h"
#include "utils.h"

using namespace std;

int main()
{
    Table table({"a", "b", "c"});
    table.addRow(1, {"1", "2", "3"});
    table.addRow(10, {"4", "5", "6"});
    table.addRow(5, {"7", "8", "9"});

    table.setValue("b", 10, "35");

    Cell c(table, "");

    auto headers = table.getHeaders();
    auto rowNumbers = table.getRowNumbers();

    auto value = table.getValue(headers[1], rowNumbers[1]);

    return 0;
}
