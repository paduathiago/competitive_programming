#include <iostream>
#include <cmath>
#include <vector>

using std::vector;

vector<long long> primeFactors(long long n)
{
    vector<long long> factors;

    if (n % 2 == 0)
    {
        factors.push_back(2);
        while (n % 2 == 0)
        {
            n /= 2;
        }
    }

    for (long long i = 3; i <= std::sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            factors.push_back(i);
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }

    if (n > 2) // current number is prime
    {
        factors.push_back(n);
    }

    return factors;
}

int main() {

    long long number;
    std::cin >> number;

    vector<long long> primes = primeFactors(number);
    int k = primes.size();

    if (k < 2) // stripped numbers require at least two prime factors
    {
        std::cout << 0 << std::endl;
    }
    else
    {
        long long result = (1LL << k) - k - 1; // 2^k - k - 1
        std::cout << result << std::endl;
    }

    return 0;
}