#include "functions.h"

#include <windows.h>
#include <conio.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
    /**
     * @brief Reads one line from standard input.
     * @param prompt Text displayed before input.
     * @return Entered line.
     * @throws std::runtime_error If the input stream is closed.
     */
    std::string input(const std::string& prompt)
    {
        std::cout << prompt;

        std::string text;

        if (!std::getline(std::cin, text))
        {
            throw std::runtime_error("Input stream closed.");
        }

        return text;
    }

    /**
     * @brief Reads a password without displaying its characters.
     * @return Entered password.
     */
    std::string passwordInput()
    {
        std::cout << "Password: ";

        std::string password;

        while (true)
        {
            int symbol = _getch();

            if (symbol == 13)
            {
                std::cout << '\n';
                return password;
            }

            if (symbol == 0 || symbol == 224)
            {
                _getch();
                continue;
            }

            if (symbol == 8)
            {
                if (!password.empty())
                {
                    password.pop_back();
                }

                continue;
            }

            if (symbol >= 32 && symbol <= 126 &&
                password.size() < 128)
            {
                password.push_back(static_cast<char>(symbol));
            }
        }
    }

    /**
     * @brief Clears the active characters of a sensitive string.
     * @param text String to clear.
     */
    void clearText(std::string& text)
    {
        if (!text.empty())
        {
            SecureZeroMemory(text.data(), text.size());
        }

        text.clear();
    }

    /**
     * @brief Creates an account with a random salt and password hash.
     */
    void registration()
    {
        logging("Registration started");

        std::string login = input(
            "Login (3-20 lowercase letters or digits): "
        );

        if (!validLogin(login))
        {
            logging("Registration rejected: invalid login");
            std::cout << "Invalid login.\n";
            return;
        }

        if (userExists(login))
        {
            logging("Registration rejected: account exists");
            std::cout << "Account already exists.\n";
            return;
        }

        std::string password = passwordInput();

        if (password.size() < 8)
        {
            clearText(password);
            logging("Registration rejected: short password");
            std::cout << "Use at least 8 characters.\n";
            return;
        }

        User user;
        user.login = login;

        Bytes salt = randomBytes(SALT_SIZE);

        std::copy(
            salt.begin(),
            salt.end(),
            user.salt.begin()
        );

        user.hash = hashing(password, user.salt);
        clearText(password);

        saveUser(user);

        logging("Registration completed");
        std::cout << "Account created.\n";
    }

    /**
     * @brief Displays masked personal data from the current account.
     * @param user Current account.
     */
    void showData(const User& user)
    {
        if (user.data.empty())
        {
            logging("Profile viewed: no personal data");
            std::cout << "No personal data saved.\n";
            return;
        }

        std::string text = decryptData(user.data);
        std::string phone;
        std::string card;
        std::string cvv;

        {
            std::istringstream stream(text);

            std::getline(stream, phone);
            std::getline(stream, card);
            std::getline(stream, cvv);
        }

        clearText(text);

        if (!validDigits(phone, 10, 15) ||
            !validDigits(card, 16, 16) ||
            !validDigits(cvv, 3, 3))
        {
            clearText(phone);
            clearText(card);
            clearText(cvv);

            throw std::runtime_error("Invalid personal data.");
        }

        std::string safePhone = masking(phone, 2);
        std::string safeCard = masking(card, 4);

        logging(
            "Profile viewed | phone=" + safePhone +
            " | card=" + safeCard +
            " | cvv=[hidden]"
        );

        std::cout << "Phone: " << safePhone << '\n'
            << "Card:  " << safeCard << '\n'
            << "CVV:   ***\n";

        clearText(phone);
        clearText(card);
        clearText(cvv);
    }

    /**
     * @brief Reads, validates, encrypts, and saves personal data.
     * @param user Current account.
     */
    void editData(User& user)
    {
        logging("Personal data editing started");

        std::string phone = input("Phone (10-15 digits): ");
        std::string card = input("Card (16 digits): ");
        std::string cvv = input("CVV (3 digits, demo only): ");

        if (!validDigits(phone, 10, 15) ||
            !validDigits(card, 16, 16) ||
            !validDigits(cvv, 3, 3))
        {
            clearText(phone);
            clearText(card);
            clearText(cvv);

            logging("Personal data rejected: invalid format");
            std::cout << "Invalid data format.\n";
            return;
        }

        std::string event =
            "Personal data saved | phone=" + masking(phone, 2) +
            " | card=" + masking(card, 4) +
            " | cvv_synthetic=" + fuzzing(cvv);

        std::string text = phone + "\n" + card + "\n" + cvv;

        Bytes encrypted = encryptData(text);

        clearText(text);
        clearText(phone);
        clearText(card);
        clearText(cvv);

        User updated = user;
        updated.data = encrypted;

        saveUser(updated);
        user.data = encrypted;

        logging(event);

        std::cout << "Personal data saved.\n";
    }

    /**
     * @brief Runs the personal account menu.
     * @param user Authenticated account.
     */
    void cabinet(User& user)
    {
        while (true)
        {
            std::cout
                << "\n Personal account \n"
                << "1 Show personal data\n"
                << "2 Edit personal data\n";

            std::string choice = input("Choice: ");

            if (choice == "1")
            {
                showData(user);
            }
            else if (choice == "2")
            {
                editData(user);
            }
            else if (choice == "0")
            {
                logging("Logout");
                return;
            }
            else
            {
                logging("Invalid personal account menu choice");
                std::cout << "Invalid choice.\n";
            }
        }
    }

    /**
     * @brief Authenticates an account and opens its personal menu.
     */
    void loginUser()
    {
        logging("Login started");

        std::string login = input("Login: ");
        std::string password = passwordInput();

        if (!validLogin(login) || !userExists(login))
        {
            clearText(password);
            logging("Login failed");
            std::cout << "Invalid login or password.\n";
            return;
        }

        User user = loadUser(login);

        std::array<unsigned char, HASH_SIZE> hash =
            hashing(password, user.salt);

        clearText(password);

        bool correct = compareHash(hash, user.hash);
        SecureZeroMemory(hash.data(), hash.size());

        if (!correct)
        {
            logging("Login failed");
            std::cout << "Invalid login or password.\n";
            return;
        }

        logging("Login successful");
        std::cout << "Login successful.\n";

        cabinet(user);
    }
}

/**
 * @brief Starts the console application and handles fatal errors.
 * @return Zero on normal exit or one on failure.
 */
int main()
{
    try
    {
        logging("Application started");

        while (true)
        {
            std::cout
                << "\n Menu \n"
                << "1 Create account\n"
                << "2 Log in\n";

            std::string choice = input("Choice: ");

            if (choice == "1")
            {
                registration();
            }
            else if (choice == "2")
            {
                loginUser();
            }
            else if (choice == "0")
            {
                logging("Application closed");
                return 0;
            }
            else
            {
                logging("Invalid main menu choice");
                std::cout << "Invalid choice.\n";
            }
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';

        try
        {
            logging("Application stopped because of an error");
        }
        catch (...)
        {
            std::cerr << "The error could not be logged.\n";
        }

        return 1;
    }
}