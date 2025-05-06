#include <iostream>
#include <vector>

using namespace std;

long long numberOfIncreasingSubsequences(int nLength, int kDesiredLength, const vector<long long>& aNumbers)
{
    vector<vector<long long>> dp(nLength + 1, vector<long long>(kDesiredLength + 1, 0));

    for (int i = 0; i <= nLength; i++)
    {
        dp[i][1] = 1;
    }

    for (int length = 2; length <= kDesiredLength; ++length)
    {
        for (int i = 0; i < nLength; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (aNumbers[j] < aNumbers[i])
                {
                    dp[i][length] += dp[j][length - 1];
                }
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < nLength; ++i)
    {
        result += dp[i][kDesiredLength];
    }

    return result;
}

int main(){
    int nLength, kDesiredLength;

    while (true)
    {
        cin >> nLength >> kDesiredLength;
        if (nLength == 0 or kDesiredLength == 0)
            break;

        vector<long long> aNumbers(nLength);
        for (int i = 0; i < nLength; i++)
        {
            cin >> aNumbers[i];
        }

        cout << numberOfIncreasingSubsequences(nLength, kDesiredLength, aNumbers) << endl;
    }

    return 0;
}