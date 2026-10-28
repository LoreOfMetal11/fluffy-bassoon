#include "functions.h"

#include <windows.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace
{
    constexpr std::uint32_t FILE_MAGIC = 0x3542414C;
    constexpr std::uint32_t MAX_DATA_SIZE = 65536;

    /**
     * @brief Builds a safe account file path.
     * @param login Valid account login.
     * @return Account file path.
     */
    std::filesystem::path userPath(const std::string& login)
    {
        if (!validLogin(login))
        {
            throw std::runtime_error(" ");
        }

        return std::filesystem::path("users") /
            ("user_" + login + ".bin");
    }
}

bool validLogin(const std::string& login)
{
    if (login.size() < 3 || login.size() > 20)
    {
        return false;
    }

    for (char symbol : login)
    {
        bool letter = symbol >= 'a' && symbol <= 'z';
        bool digit = symbol >= '0' && symbol <= '9';

        if (!letter && !digit)
        {
            return false;
        }
    }

    return true;
}


bool validDigits(
    const std::string& text,
    std::size_t minSize,
    std::size_t maxSize)
{
    if (text.size() < minSize || text.size() > maxSize)
    {
        return false;
    }

    for (char symbol : text)
    {
        if (symbol < '0' || symbol > '9')
        {
            return false;
        }
    }

    return true;
}


bool userExists(const std::string& login)
{
    return std::filesystem::exists(userPath(login));
}


void saveUser(const User& user)
{
    std::filesystem::path path = userPath(user.login);

    if (user.data.size() > MAX_DATA_SIZE)
    {
        throw std::runtime_error(" ");
    }

    std::filesystem::create_directories("users");

    std::filesystem::path temp = path;
    temp += ".tmp";

    std::ofstream file(temp, std::ios::binary | std::ios::trunc);

    if (!file)
    {
        throw std::runtime_error(" ");
    }

    std::uint32_t magic = FILE_MAGIC;
    std::uint32_t loginSize =
        static_cast<std::uint32_t>(user.login.size());
    std::uint32_t dataSize =
        static_cast<std::uint32_t>(user.data.size());

    file.write(
        reinterpret_cast<const char*>(&magic),
        sizeof(magic)
    );

    file.write(
        reinterpret_cast<const char*>(&loginSize),
        sizeof(loginSize)
    );

    file.write(user.login.data(), loginSize);

    file.write(
        reinterpret_cast<const char*>(user.salt.data()),
        static_cast<std::streamsize>(user.salt.size())
    );

    file.write(
        reinterpret_cast<const char*>(user.hash.data()),
        static_cast<std::streamsize>(user.hash.size())
    );

    file.write(
        reinterpret_cast<const char*>(&dataSize),
        sizeof(dataSize)
    );

    if (!user.data.empty())
    {
        file.write(
            reinterpret_cast<const char*>(user.data.data()),
            static_cast<std::streamsize>(user.data.size())
        );
    }

    file.close();

    if (!file)
    {
        std::filesystem::remove(temp);
        throw std::runtime_error(" ");
    }

    if (!MoveFileExW(
        temp.c_str(),
        path.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
    {
        std::filesystem::remove(temp);
        throw std::runtime_error(" ");
    }
}


User loadUser(const std::string& login)
{
    std::ifstream file(userPath(login), std::ios::binary);

    if (!file)
    {
        throw std::runtime_error(" ");
    }

    User user;
    std::uint32_t magic = 0;
    std::uint32_t loginSize = 0;
    std::uint32_t dataSize = 0;

    file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
    file.read(
        reinterpret_cast<char*>(&loginSize),
        sizeof(loginSize)
    );

    if (!file || magic != FILE_MAGIC ||
        loginSize < 3 || loginSize > 20)
    {
        throw std::runtime_error(" ");
    }

    user.login.resize(loginSize);
    file.read(user.login.data(), loginSize);

    file.read(
        reinterpret_cast<char*>(user.salt.data()),
        static_cast<std::streamsize>(user.salt.size())
    );

    file.read(
        reinterpret_cast<char*>(user.hash.data()),
        static_cast<std::streamsize>(user.hash.size())
    );

    file.read(
        reinterpret_cast<char*>(&dataSize),
        sizeof(dataSize)
    );

    if (!file || user.login != login || dataSize > MAX_DATA_SIZE)
    {
        throw std::runtime_error(" ");
    }

    user.data.resize(dataSize);

    if (!user.data.empty())
    {
        file.read(
            reinterpret_cast<char*>(user.data.data()),
            static_cast<std::streamsize>(user.data.size())
        );
    }

    if (!file ||
        file.peek() != std::char_traits<char>::eof())
    {
        throw std::runtime_error(" ");
    }

    return user;
}