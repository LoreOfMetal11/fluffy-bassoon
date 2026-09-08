#include "cipher.h"

std::string Encrypt(
    const std::string& text, const std::string& alphabet, int shift)
{
    std::string result = "";
    int alphasize = static_cast<int>(alphabet.size());

    // Make shift smaller if it is bigger than the alphabet.
    shift = shift % alphasize;

    for (char symbol : text)
    {
        int position = -1;

        // Find the symbol position in the alphabet.
        for (int i = 0; i < alphasize; i++)
        {
            if (alphabet[i] == symbol)
            {
                position = i;
                break;
            }
        }

        if (position == -1)
        {
            // Keep symbols that are not in the alphabet.
            result += symbol;
        }
        else
        {
            // Use Y = (X + K) mod N.
            int newpos = (position + shift) % alphasize;
            result += alphabet[newpos];
        }
    }

    return result;
}

std::string Decrypt(
    const std::string& text,const std::string& alphabet,int shift)
{
    std::string result = "";
    int alphasize = static_cast<int>(alphabet.size());

    // Make shift smaller if it is bigger than the alphabet.
    shift = shift % alphasize;

    for (char symbol : text)
    {
        int position = -1;

        // Find the symbol position in the alphabet.
        for (int i = 0; i < alphasize; i++)
        {
            if (alphabet[i] == symbol)
            {
                position = i;
                break;
            }
        }

        if (position == -1)
        {
            // Keep symbols that are not in the alphabet.
            result += symbol;
        }
        else
        {
            // Add alphabet size to avoid a negative number.
            int newpos = (position - shift + alphasize) % alphasize;
            result += alphabet[newpos];
        }
    }

    return result;
}