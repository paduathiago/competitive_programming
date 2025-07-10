#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX = 100'000;

vector<bool> is_prime(MAX + 1, true);

void sieve()
{
    is_prime[0] = is_prime[1] = false;

    int limit = static_cast<int>(sqrt(MAX)) + 1;
    for (int i = 2; i <= limit; ++i)
    {
        if (is_prime[i])
        {
            for (int j = i + i; j <= MAX; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int N;

    while (cin >> N)
    {
        bool isPrime = is_prime[N];
        bool areAllDigitsPrime = true;

        while (N > 0)
        {
            int digit = N % 10;
            if (!is_prime[digit])
            {
                areAllDigitsPrime = false;
                break;
            }
            N /= 10;
        }

        if (isPrime && areAllDigitsPrime)
            cout << "Super" << endl;
        else if (isPrime)
            cout << "Primo" << endl;
        else
            cout << "Nada" << endl;
    }

    return 0;
}