#ifndef CRT_H
#define CRT_H

#include <vector>

using namespace std;

/// @brief Stores one congruence x = rem (mod mod).
struct Congruence
{
    long long rem;
    long long mod;
};

/// @brief Finds gcd and Bezout coefficients.
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
);

/// @brief Finds inverse of a modulo mod.
/// @param a Number to invert.
/// @param mod Modulus.
/// @return Modular inverse or -1 if it does not exist.
long long modinverse(long long a, long long mod);

/// @brief Checks whether two numbers are coprime.
/// @param a First nãmber.
/// @param b Second number.
/// @return true if gcd(a, b) equals 1.
bool coprime(long long a, long long b);

/// @brief Checks whether CRT can be applied to a system.
/// @param list System of congruences.
/// @return true if all moduli are greater than 1 and pairwise coprime.
bool compatible(const vector<Congruence>& list);

/// @brief Solves a system using the Chinese remainder theorem.
/// @param list System of congruences.
/// @return Smallest non-negative solution or -1 on error.
long long chineseremainder(const vector<Congruence>& list);

/// @brief Prints a system of congruences.
/// @param list System to print.
void printcongruences(const vector<Congruence>& list);

#endif