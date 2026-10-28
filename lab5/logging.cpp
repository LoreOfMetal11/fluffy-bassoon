#include "functions.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <stdexcept>

/**
 * @brief Masks all characters except the last visible characters.
 * @param text Original text.
 * @param visible Number of characters to leave visible.
 * @return Masked text.
 */
std::string masking(const std::string& text, std::size_t visible)
{
    if (text.empty())
    {
        return "";
    }

    if (visible >= text.size())
    {
        return std::string(text.size(), '*');
    }

    std::size_t hidden = text.size() - visible;

    return std::string(hidden, '*') + text.substr(hidden);
}

/**
 * @brief Replaces each digit with a different random digit for logging.
 * @param text Original digit string.
 * @return Synthetic digit string.
 */
std::string fuzzing(const std::string& text)
{
    if (!validDigits(text, 1, 32))
    {
        throw std::runtime_error(" ");
    }

    Bytes random = randomBytes(text.size());
    std::string result = text;

    for (std::size_t i = 0; i < text.size(); ++i)
    {
        int digit = text[i] - '0';
        int offset = 1 + random[i] % 9;

        result[i] = static_cast<char>(
            '0' + (digit + offset) % 10
            );
    }

    return result;
}

/**
 * @brief Writes a timestamped event to the application log.
 * @param action Event description without raw sensitive values.
 * @throws std::runtime_error If writing fails.
 */
void logging(const std::string& action)
{
    std::ofstream file("actions.log", std::ios::app);

    if (!file)
    {
        throw std::runtime_error(" ");
    }

    std::time_t now = std::time(nullptr);
    std::tm time{};

    if (localtime_s(&time, &now) != 0)
    {
        throw std::runtime_error(" ");
    }

    file << std::put_time(&time, "%Y-%m-%d %H:%M:%S")
        << " | " << action << '\n';

    file.flush();

    if (!file)
    {
        throw std::runtime_error(" ");
    }
}