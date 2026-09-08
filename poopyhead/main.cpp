#include <iostream>
#include <limits>
#include <string>
#include "cipher.h"

/// @brief Prints a short guide for console arguments.
/// @details The program needs mode, shift, alphabet and text.
/// Text with spaces must be written inside quotation marks.
void helpme()
{
    std::cout << "Console mode:\n";
    std::cout << "cipher.exe encrypt 3 \"alphabet\" \"text\"\n";
    std::cout << "cipher.exe decrypt 3 \"alphabet\" \"text\"\n";
    std::cout << "\n";
    std::cout << "Example:\n";
    std::cout << "cipher.exe encrypt 3 \"àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ0123456789 .,!?\" \"ïðèâåò, ìèð!\"\n";
}

/// @brief Checks if the entered mode can be used.
/// @param mode Mode entered by the user or passed in console.
/// @return true for encrypt or decrypt mode, otherwise false.
bool correct(const std::string& mode)
{
    return mode == "encrypt" || mode == "decrypt";
}

/// @brief Runs encryption or decryption using selected mode.
/// @param mode Program mode: encrypt or decrypt.
/// @param text Text that will be processed.
/// @param alphabet Alphabet used for moving symbols.
/// @param shift Number of positions for the shift.
/// @return Result text after encryption or decryption.
std::string postext( const std::string& mode, const std::string& text, const std::string& alphabet, int shift)
{
    // Choose the needed function based on user mode.
    if (mode == "encrypt")
    {
        return Encrypt(text, alphabet, shift);
    }

    return Decrypt(text, alphabet, shift);
}

/// @brief Starts the program in interactive mode.
/// @details The program asks the user for alphabet, mode, shift and text.
void sussybaka()
{
    std::string alphabet;
    std::string mode;
    std::string text;
    int shift;

    std::cout << "Interactive mode\n\n";

    std::cout << "Enter alphabet: ";
    std::getline(std::cin, alphabet);
    std::cout << "Enter mode (encrypt/decrypt): ";
    std::getline(std::cin, mode);
    std::cout << "Enter shift: ";
    std::cin >> shift;

    // Remove Enter left after reading the number.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::string result = postext(mode, text, alphabet, shift);

    std::cout << "\nResult: " << result << "\n";
}

/// @brief Starts the program using console arguments.
/// @details Required order: mode, shift, alphabet, text.
/// @param argc Number of received console arguments.
/// @param argv Array with console argument values.
void console(int argc, char* argv[])
{
    std::string mode = argv[1]; int shift = std::stoi(argv[2]); std::string alphabet = argv[3]; std::string text = argv[4];

    std::string result = postext(mode, text, alphabet, shift);

    std::cout << "Result: " << result << "\n";
}

/// @brief Starts console or interactive program mode.
/// @param argc Number of command line arguments.
/// @param argv Command line argument list.
/// @return 0 when the program finishes normally.
int main(int argc, char* argv[])
{
    // Arguments mean console mode; no arguments mean interactive mode.
    if (argc > 1)
    {
        console(argc, argv);
    }
    else
    {
        sussybaka();
    }

    return 0;
}