#include "cipher.h"

#include <cstdlib>
#include <ctime>

std::string tablemake(std::string alphabet)
{
    // Copy the alphabet because the original alphabet must stay unchanged.
    std::string table = alphabet;

    std::srand(std::time(0));

    for (int i = 0; i < table.size(); i++)
    {
        int randplace = std::rand() % table.size();

        // Change two symbols places.
        char temp = table[i];
        table[i] = table[randplace];
        table[randplace] = temp;
    }

    return table;
}

std::string Encrypt(
    std::string text,
    std::string alphabet,
    std::string table
)
{
    std::string result = "";

    for (int i = 0; i < text.size(); i++)
    {
        for (int j = 0; j < alphabet.size(); j++)
        {
            // If a symbol is found, take a new symbol from the same place.
            if (text[i] == alphabet[j])
            {
                result += table[j];
                break;
            }

            // Keep a symbol when it is not in the alphabet.
            if (j == alphabet.size() - 1)
            {
                result += text[i];
            }
        }
    }

    return result;
}

std::string Decrypt(
    std::string text,
    std::string alphabet,
    std::string table
)
{
    std::string result = "";

    for (int i = 0; i < text.size(); i++)
    {
        for (int j = 0; j < table.size(); j++)
        {
            // Find symbol in the table and return alphabet symbol from this place.
            if (text[i] == table[j])
            {
                result += alphabet[j];
                break;
            }

            // Keep a symbol when it is not in the table.
            if (j == table.size() - 1)
            {
                result += text[i];
            }
        }
    }

    return result;
}