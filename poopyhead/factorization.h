#ifndef FACTORIZATION_H
#define FACTORIZATION_H

#include <vector>

/// @brief Factorizes a number by checking possible divisors.
/// @param number Positive integer to factorize.
/// @return Prime factors with repetitions.
std::vector<long long> dividefactor(long long number);

/// @brief Factorizes a number using Fermat's factorization method.
/// @param number Odd positive integer to factorize.
/// @return Two factors or the original number if factorization failed.
std::vector<long long> fermatfactor(long long number);

/// @brief Prints factorization result.
/// @param number Original number.
/// @param factors Prime or composite factors.
void printfactors(long long number, const std::vector<long long>& factors);

#endif