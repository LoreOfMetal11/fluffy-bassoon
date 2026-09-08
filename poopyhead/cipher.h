#ifndef CIPHER_H
#define CIPHER_H
#include <string>

/// @brief Encrypts text by moving each supported symbol forward.
/// @param text Original text.
/// @param alphabet Symbols used by the program.
/// @param shift Number of positions for moving symbols.
/// @return Encrypted text.
std::string Encrypt( const std::string& text, const std::string& alphabet, int shift);

/// @brief Decrypts text by moving each supported symbol backward.
/// @param text Encrypted text.
/// @param alphabet Symbols used by the program.
/// @param shift Number of positions used during encryption.
/// @return Decrypted text.
std::string Decrypt( const std::string& text, const std::string& alphabet, int shift);

#endif