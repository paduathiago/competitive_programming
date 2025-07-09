#include <iostream>
#include <bitset>

using namespace std;

const int MAX = 2e6 + 1;

bitset<MAX> is_prime;
int hyperprime_count[MAX];
int divisorCount[MAX];

void precompute()
{
    for (int i = 2; i < MAX; ++i)
    {
        if (is_prime[i]) {
            hyperprime_count[i] = hyperprime_count[i - 1] + 1;

            for (long long j = i * 2; j < MAX; j += i)
            {
                is_prime[j] = false;

                int power = 0;
                int temp = j;
                while (temp % i == 0) {
                    ++power;
                    temp /= i;
                }

                if (divisorCount[j] == 0)
                    divisorCount[j] = power + 1;
                else
                    divisorCount[j] *= (power + 1);
            }
        }
        else
        {
            if (is_prime[divisorCount[i]])
                hyperprime_count[i] = hyperprime_count[i - 1] + 1;
            else
                hyperprime_count[i] = hyperprime_count[i - 1];
        }
    }
}

int main() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;

    precompute();

    int N;
    while (cin >> N)
    {
        cout << hyperprime_count[N] << endl;
    }

    return 0;
}
