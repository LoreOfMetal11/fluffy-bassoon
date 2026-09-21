#include "factorization.h"
#include <cmath>
#include <iostream>

using namespace std;

vector<long long> dividefactor(long long number)
{
    vector<long long> factors;

    if (number < 2)
    {
        return factors;
    }

    while (number % 2 == 0)
    {
        factors.push_back(2);
        number /= 2;
    }

    for (long long divisor = 3; divisor <= number / divisor; divisor += 2)
    {
        while (number % divisor == 0)
        {
            factors.push_back(divisor);
            number /= divisor;
        }
    }

    if (number > 1)
    {
        factors.push_back(number);
    }

    return factors;
}

vector<long long> fermatfactor(long long number)
{
    vector<long long> factors;

    if (number < 2)
    {
        return factors;
    }

    if (number % 2 == 0)
    {
        factors.push_back(2);
        factors.push_back(number / 2);
        return factors;
    }

    long long root = static_cast<long long>(sqrt(static_cast<long double>(number)));

    if (root * root < number)
    {
        root++;
    }

    // Fermat searches for representation number = x^2 - y^2.
    // A small cache of the previous square makes the loop more readable
    // and avoids recalculating x * x in the same iteration.
    for (long long x = root; x <= number; x++)
    {
        long long square = x * x - number;
        long long y = static_cast<long long>(sqrt(static_cast<long double>(square)));

        if (y * y == square)
        {
            long long first = x - y;
            long long second = x + y;

            factors.push_back(first);
            factors.push_back(second);
            return factors;
        }
    }

    factors.push_back(number);
    return factors;
}

void printfactors(long long number, const vector<long long>& factors)
{
    cout << number << " = ";

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