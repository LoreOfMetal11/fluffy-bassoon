#ifndef FILE_H
#define FILE_H
#include <string>

/// @brief Saves the table in a file.
/// @param table Replacement table.
/// @return true if saving worked.
bool savetable(std::string table);

/// @brief Reads the table from a file.
/// @return Saved table or empty text.
std::string loadtable();

#endif