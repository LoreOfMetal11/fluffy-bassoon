#include "file.h"
#include <fstream>

bool savetable(std::string table)
{
    std::ofstream file("table.txt");

    // Stop if the file cannot be opened.
    if (!file)
    {
        return false;
    }

    file << table;
    file.close();

    return true;
}

std::string loadtable()
{
    std::ifstream file("table.txt");
    std::string table;

    // Return empty text if the table file does not exist.
    if (!file)
    {
        return "";
    }

    std::getline(file, table);
    file.close();

    return table;
}