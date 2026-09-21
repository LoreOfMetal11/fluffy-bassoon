#include <chrono>
#include <iostream>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
#include "factorization.h"
#include "prime.h"

using namespace std;
using Clock = chrono::steady_clock;

void menu()
{
    cout << "\n1  Factorization by possible divisors\n";
    cout << "2  Factorization by Fermat method\n";
    cout << "3  Sieve of Eratosthenes\n";
    cout << "4  Perfect numbers\n";
    cout << "0  Exit\n";
    cout << " ";
}

void printTime(Clock::time_point start, Clock::time_point finish)
{
    auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start);
    cout << "Time: " << elapsed.count() << " microseconds\n";
}

long long readnumber()
{
    long long number;

    cout << "Number: ";
    cin >> number;

    return number;
}

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

        Clock::time_point start;
        Clock::time_point finish;

        switch (choice)
        {
        case 1:
        {
            long long number = readnumber();

            start = Clock::now();
            vector<long long> factors = dividefactor(number);
            finish = Clock::now();

            printfactors(number, factors);
            break;
        }
        case 2:
        {
            long long number = readnumber();

            start = Clock::now();
            vector<long long> factors = fermatfactor(number);
            finish = Clock::now();

            printfactors(number, factors);
            break;
        }
        case 3:
        {
            int limit;

            cout << "Maximum value: ";
            cin >> limit;

            if (limit < 1)
            {
                cout << "The limit must be positive.\n";
                break;
            }

            start = Clock::now();
            vector<bool> prime_table = sieve(limit);
            finish = Clock::now();

            printprimes(limit, prime_table);
            break;
        }
        case 4:
        {
            int limit;

            cout << "Maximum value: ";
            cin >> limit;

            if (limit < 1)
            {
                cout << "The limit must be positive.\n";
                break;
            }

            start = Clock::now();
            vector<bool> prime_table = sieve(limit);

            cout << "Perfect numbers:\n";

            for (int number = 2; number <= limit; number++)
            {
                if (perfect(number, prime_table))
                {
                    cout << number << ' ';
                }
            }

            cout << '\n';
            finish = Clock::now();
            break;
        }
        }

        if (choice >= 1 && choice <= 4)
        {
            printTime(start, finish);
        }
    } while (choice != 0);

    return 0;
}