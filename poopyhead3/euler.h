#ifndef EULER_H
#define EULER_H

#include <vector>

using namespace std;

/// @brief Finds prime factors of a number.
/// @param num Number to factorize.
/// @return Vector containing prime factors with repetitions.
vector<long long> primefac(long long num);

/// @brief Calculates Euler's totient function.
/// @param num Positive input number.
/// @return Number of positive integers coprime with num.
long long eulerfunc(long long num);

/// @brief Prints prime factorization of a number.
/// @param num Original number.
/// @param factors Prime factors of the number.
void prfac(long long num, const vector<long long>& factors);

#endif