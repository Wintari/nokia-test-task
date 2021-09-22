#include <iostream>
#include <fstream>
#include "table.h"
#include "csvio.h"
#include "errors.h"

using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        if(argc == 1)
        {
            std::ifstream file(argv[1]);
            if(file.is_open())
            {
                CsvReader reader;
                CsvWriter writer;

                Table table = reader.readCsvTable(file);

                writer.writeCsvTable(std::cout, table);

                file.close();
            }
            else
            {
                throw FileNotFoundError;
            }
        }
    }
    catch (std::string e)
    {
        std::cout << e << std::endl;
    }

    return 0;
}
