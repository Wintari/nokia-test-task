#include <iostream>
#include <fstream>
#include "table.h"
#include "csvio.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        std::ifstream file(argv[1]);

        CsvReader reader;
        CsvWriter writer;

        Table table = reader.readCsvTable(file);

        writer.writeCsvTable(std::cout, table);
    }

    return 0;
}
