#include "prime.h"
#include <iostream>

using namespace std;

vector<bool> sieve(int limit)
{
    vector<bool> prime_table(limit + 1, true);

    if (limit >= 1)
    {
        prime_table[1] = false;
    }

    for (int prime = 2; prime <= limit / prime; prime++)
    {
        if (prime_table[prime])
        {
            for (int multiple = prime * prime; multiple <= limit; multiple += prime)
            {
                prime_table[multiple] = false;
            }
        }
    }

    return prime_table;
}

long long propersum(long long number, const vector<bool>& prime_table)
{
    if (number <= 1)
    {
        return 0;
    }

    long long sum = 1;

    for (long long divisor = 2; divisor <= number / divisor; divisor++)
    {
        if (number % divisor == 0)
        {
            long long other = number / divisor;
            sum += divisor;

            if (other != divisor)
            {
                sum += other;
            }
        }
    }

    return sum;
}

bool perfect(long long number, const vector<bool>& prime_table)
{
    return number > 1 && propersum(number, prime_table) == number;
}

void printprimes(int limit, const vector<bool>& prime_table)
{
    cout << "Prime numbers up to " << limit << ":\n";

    for (int number = 2; number <= limit; number++)
    {
        if (prime_table[number])
        {
            cout << number << ' ';
        }
    }

    cout << '\n';
}