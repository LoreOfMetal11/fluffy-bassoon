#ifndef STORAGE_H
#define STORAGE_H

#include "security.h"

#include <array>
#include <cstddef>
#include <string>

struct User
{
    std::string login;

    std::array<unsigned char, SALT_SIZE> salt{};

    std::array<unsigned char, HASH_SIZE> hash{};

    Bytes data;
};


bool validLogin(const std::string& login);


bool validDigits(
    const std::string& text,
    std::size_t minSize,
    std::size_t maxSize
);


bool userExists(const std::string& login);


void saveUser(const User& user);

/**
 * @brief Loads and validates an account from a binary file.
 * @param login Account login.
 * @return Loaded account.
 * @throws std::runtime_error If the login or account file is invalid.
 */
User loadUser(const std::string& login);

#endif