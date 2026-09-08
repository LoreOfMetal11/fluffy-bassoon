#ifndef CIPHER_H
#define CIPHER_H
#include <string>

/// @brief Creates a new replacement table.
/// @param alphabet Program alphabet.
/// @return Mixed alphabet for encryption.
std::string tablemake(std::string alphabet);

/// @brief Encrypts the text.
/// @param text Original text.
/// @param alphabet Normal alphabet.
/// @param table Mixed alphabet.
/// @return Encrypted text.
std::string Encrypt(std::string text, std::string alphabet, std::string table);

/// @brief Decrypts the text.
/// @param text Encrypted text.
/// @param alphabet Normal alphabet.
/// @param table Mixed alphabet.
/// @return Decrypted text.
std::string Decrypt(std::string text, std::string alphabet, std::string table);

#endif