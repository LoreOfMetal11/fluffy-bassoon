#include "crt.h"
#include <iostream>

using namespace std;

/// @brief Finds gcd and Bezout coefficients recursively.
/// @param a First number.
/// @param b Second number.
/// @param x First Bezout coefficient.
/// @param y Second Bezout coefficient.
/// @return Greatest common divisor of a and b.
long long extendedgcd(
    long long a,
    long long b,
    long long& x,
    long long& y
)
{
    if (b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    long long oldx;
    long long oldy;

    long long gcd = extendedgcd(b, a % b, oldx, oldy);

    x = oldy;
    y = oldx - (a / b) * oldy;

    return gcd;
}

/// @brief Finds a multiplicative inverse modulo mod.
/// @param a Number to invert.
/// @param mod Modulus.
/// @return Value x where a * x = 1 (mod mod), or -1 on error.
long long modinverse(long long a, long long mod)
{
    long long x;
    long long y;

    long long gcd = extendedgcd(a, mod, x, y);

    if (gcd != 1)
    {
        return -1;
    }

    x %= mod;

    if (x < 0)
    {
        x += mod;
    }

    return x;
}

/// @brief Checks whether gcd(a, b) is equal to 1.
/// @param a First number.
/// @param b Second number.
/// @return true if numbers are coprime.
bool coprime(long long a, long long b)
{
    long long x;
    long long y;

    long long gcd = extendedgcd(a, b, x, y);

    return gcd == 1;
}

/// @brief Checks whether CRT requirements are satisfied.
/// @param list System of congruences.
/// @return true if moduli are valid and pairwise coprime.
bool compatible(const vector<Congruence>& list)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (list[i].mod <= 1)
        {
            return false;
        }

        for (size_t j = i + 1; j < list.size(); j++)
        {
            if (!coprime(list[i].mod, list[j].mod))
            {
                return false;
            }
        }
    }

    return true;
}

/// @brief Combines congruences into one CRT solution.
/// @param list System of congruences.
/// @return Smallest non-negative solution or -1 if CRT cannot be used.
long long chineseremainder(const vector<Congruence>& list)
{
    if (list.empty())
    {
        return 0;
    }

    if (!compatible(list))
    {
        return -1;
    }

    long long allmod = 1;

    for (const Congruence& item : list)
    {
        allmod *= item.mod;
    }

    long long result = 0;

    for (const Congruence& item : list)
    {
        long long rem = item.rem % item.mod;

        if (rem < 0)
        {
            rem += item.mod;
        }

        long long part = allmod / item.mod;
        long long inv = modinverse(part, item.mod);

        if (inv == -1)
        {
            return -1;
        }

        result += rem * part * inv;
        result %= allmod;
    }

    if (result < 0)
    {
        result += allmod;
    }

    return result;
}

/// @brief Prints all congruences from a system.
/// @param list System of congruences.
void printcongruences(const vector<Congruence>& list)
{
    cout << "System:\n";

    for (const Congruence& item : list)
    {
        cout << "x = " << item.rem << " (mod " << item.mod << ")\n";
    }
}