#ifndef PRIME_H
#define PRIME_H

#include <vector>

/// @brief Builds a prime-number table using the Sieve of Eratosthenes.
/// @param limit Maximum value in the table.
/// @return Boolean table where true means prime.
std::vector<bool> sieve(int limit);

/// @brief Calculates the sum of proper divisors of a number.
/// @param number Number to inspect.
/// @param prime_table Prime table used for quicker divisor processing.
/// @return Sum of all positive divisors except the number itself.
long long propersum(long long number, const std::vector<bool>& prime_table);

/// @brief Checks whether a number is perfect.
/// @param number Number to inspect.
/// @param prime_table Prime table.
/// @return True if the number equals the sum of proper divisors.
bool perfect(long long number, const std::vector<bool>& prime_table);

/// @brief Prints prime table results.
/// @param limit Maximum value.
/// @param prime_table Table returned by sieve.
void printprimes(int limit, const std::vector<bool>& prime_table);

#endif