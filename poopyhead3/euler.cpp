#include "euler.h"
#include <iostream>

using namespace std;

/// @brief Finds prime factors using trial division.
/// @param num Number to factorize.
/// @return Vector of prime factors in ascending order.
vector<long long> primefac(long long num)
{
    vector<long long> factors;

    if (num < 2)
    {
        return factors;
    }

    // Process divisor 2 separately.
    while (num % 2 == 0)
    {
        factors.push_back(2);
        num /= 2;
    }

    // num / div avoids overflow in div * div.
    for (long long div = 3; div <= num / div; div += 2)
    {
        while (num % div == 0)
        {
            factors.push_back(div);
            num /= div;
        }
    }

    // A remaining value greater than 1 is prime.
    if (num > 1)
    {
        factors.push_back(num);
    }

    return factors;
}

/// @brief Calculates Euler's totient using unique prime factors.
/// @param num Positive input number.
/// @return Euler's totient value phi(num).
long long eulerfunc(long long num)
{
    if (num == 1)
    {
        return 1;
    }

    if (num < 1)
    {
        return 0;
    }

    long long result = num;
    vector<long long> factors = primefac(num);

    for (size_t i = 0; i < factors.size(); i++)
    {
        // Each different prime factor is used once.
        if (i == 0 || factors[i] != factors[i - 1])
        {
            result -= result / factors[i];
        }
    }

    return result;
}

/// @brief Prints a number and its prime factorization.
/// @param num Original number.
/// @param factors Prime factors to print.
void prfac(long long num, const vector<long long>& factors)
{
    cout << num << " = ";

    if (factors.empty())
    {
        cout << "factorization is impossible";
    }
    else
    {
        for (size_t i = 0; i < factors.size(); i++)
        {
            cout << factors[i];

            if (i + 1 < factors.size())
            {
                cout << " * ";
            }
        }
    }

    cout << '\n';
}