#include <iostream>
#include <string>
#include "cipher.h"
#include "file.h"

/// @brief Starts the program with user input.
/// @return Nothing.
void interactive()
{
    std::string alphabet =
        "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ"
        "0123456789 .,!?";

    std::string table = loadtable();

    // Make a table only if there is no saved table.
    if (table == "")
    {
        table = tablemake(alphabet);
        savetable(table);
    }

    std::string mode;
    std::string text;

    std::cout << "Mode (encrypt/decrypt): ";
    std::getline(std::cin, mode);

    std::cout << "Text: ";
    std::getline(std::cin, text);

    if (mode == "encrypt")
    {
        std::cout << "Result: " << Encrypt(text, alphabet, table) << "\n";
    }
    else if (mode == "decrypt")
    {
        std::cout << "Result: " << Decrypt(text, alphabet, table) << "\n";
    }
}

/// @brief Starts the program with console arguments.
/// @param argc Number of values in console.
/// @param argv Values from console.
/// @return Nothing.
void console(int argc, char* argv[])
{
    std::string alphabet =
        "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ"
        "0123456789 .,!?";

    std::string table = loadtable();

    // Make a table if it was not saved before.
    if (table == "")
    {
        table = tablemake(alphabet);
        savetable(table);
    }

    std::string mode = argv[1];
    std::string text = argv[2];

    if (mode == "encrypt")
    {
        std::cout << "Result: " << Encrypt(text, alphabet, table) << "\n";
    }
    else if (mode == "decrypt")
    {
        std::cout << "Result: " << Decrypt(text, alphabet, table) << "\n";
    }
}

/// @brief Chooses program mode.
/// @param argc Number of console arguments.
/// @param argv Console arguments.
/// @return 0 after program finish.
int main(int argc, char* argv[])
{
    // No arguments means the program will ask the user for data.
    if (argc == 1)
    {
        interactive();
    }
    else
    {
        console(argc, argv);
    }

    return 0;
}