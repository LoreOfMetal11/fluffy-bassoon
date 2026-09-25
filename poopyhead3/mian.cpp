#include <chrono>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "euler.h"
#include "crt.h"

using namespace std;
using Clock = chrono::steady_clock;

/// @brief Stores a menu item number and its text.
struct MenuItem
{
    int num;
    const char* text;
};

/// @brief Prints the main menu.
void menu()
{
    const MenuItem items[] =
    {
        { 1, "Euler function" },
        { 2, "Extended Euclidean algorithm" },
        { 3, "Chinese remainder theorem" },
        { 0, "Exit" }
    };

    cout << '\n';

    for (const MenuItem& item : items)
    {
        cout << item.num << "  " << item.text << '\n';
    }

    cout << " ";
}

/// @brief Prints elapsed execution time in microseconds.
/// @param start Start time point.
/// @param finish Finish time point.
void printtime(
    Clock::time_point start,
    Clock::time_point finish
)
{
    auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start);

    cout << "Time: " << elapsed.count() << " microseconds\n";
}

/// @brief Reads one integer number from the console.
/// @return Number entered by the user.
long long readnumber()
{
    long long num;

    cout << "Number: ";
    cin >> num;

    return num;
}

/// @brief Reads number of congruences.
/// @return Number of congruences entered by the user.
int readcount()
{
    int count;

    cout << "Number of congruences: ";
    cin >> count;

    return count;
}

/// @brief Reads one congruence from the console.
/// @param num Number of the congruence.
/// @return Congruence entered by the user.
Congruence readcongruence(int num)
{
    Congruence item;

    cout << "Remainder " << num << ": ";
    cin >> item.rem;

    cout << "Modulus " << num << ": ";
    cin >> item.mod;

    return item;
}

/// @brief Runs Euler's totient function calculation.
void runeuler()
{
    long long num = readnumber();

    if (num < 1)
    {
        cout << "The number must be positive.\n";
        return;
    }

    Clock::time_point start = Clock::now();

    vector<long long> factors = primefac(num);
    long long result = eulerfunc(num);

    Clock::time_point finish = Clock::now();

    prfac(num, factors);

    cout << "Euler function: phi(" << num << ") = " << result << '\n';

    printtime(start, finish);
}

/// @brief Runs the extended Euclidean algorithm.
void runeuclid()
{
    long long a;
    long long b;

    cout << "First number: ";
    cin >> a;

    cout << "Second number: ";
    cin >> b;

    Clock::time_point start = Clock::now();

    long long x;
    long long y;
    long long gcd = extendedgcd(a, b, x, y);

    Clock::time_point finish = Clock::now();

    cout << "gcd(" << a << ", " << b << ") = " << gcd << '\n';
    cout << "x = " << x << '\n';
    cout << "y = " << y << '\n';
    cout << a << " * " << x << " + " << b << " * " << y << " = " << gcd << '\n';

    printtime(start, finish);
}

/// @brief Reads and solves a CRT system.
void runcrt()
{
    int count = readcount();

    vector<Congruence> list;

    for (int i = 1; i <= count; i++)
    {
        list.push_back(readcongruence(i));
    }

    printcongruences(list);

    if (!compatible(list))
    {
        cout << "The moduli must be pairwise coprime and greater than 1.\n";
        return;
    }

    Clock::time_point start = Clock::now();

    long long result = chineseremainder(list);

    Clock::time_point finish = Clock::now();

    long long allmod = 1;

    for (const Congruence& item : list)
    {
        allmod *= item.mod;
    }

    cout << "Solution:\n";
    cout << "x = " << result << " (mod " << allmod << ")\n";

    printtime(start, finish);
}

/// @brief Starts the console program.
/// @return 0 if the program finishes normally.
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int choice;

    do
    {
        menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            runeuler();
            break;

        case 2:
            runeuclid();
            break;

        case 3:
            runcrt();
            break;

        case 0:
            cout << "Goodbye.\n";
            break;
        }

    } while (choice != 0);

    return 0;
}