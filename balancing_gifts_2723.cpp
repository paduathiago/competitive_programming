#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_DIFF = 5;

bool solve(int N, const vector<int>& weights)
{
    bool dp[2][2 * MAX_DIFF + 1];
    memset(dp, false, sizeof(dp));
    dp[0][MAX_DIFF] = true;

    for (int i = 0; i < N; ++i)
    {
        int curr = i % 2;
        int next = (i + 1) % 2;
        memset(dp[next], false, sizeof(dp[next]));

        for (int diff = -MAX_DIFF; diff <= MAX_DIFF; ++diff)
        {
            if (!dp[curr][diff + MAX_DIFF]) continue;

            int new_diff_A = diff + weights[i];
            if (abs(new_diff_A) <= MAX_DIFF)
            {
                dp[next][new_diff_A + MAX_DIFF] = true;
            }

            int new_diff_B = diff - weights[i];
            if (abs(new_diff_B) <= MAX_DIFF)
            {
                dp[next][new_diff_B + MAX_DIFF] = true;
            }
        }
    }

    for (int diff = -MAX_DIFF; diff <= MAX_DIFF; ++diff)
    {
        if (dp[N % 2][diff + MAX_DIFF])
        {
            return true;
        }
    }
    return false;
}

int main() {
    unsigned tests, nGifts;
    vector<int> weights;

    cin >> tests;

    for (unsigned i = 0; i < tests; ++i)
    {
        cin >> nGifts;
        weights.resize(nGifts);
        for (unsigned j = 0; j < nGifts; ++j)
        {
            cin >> weights[j];
        }

        if (solve(nGifts, weights))
            cout << "Feliz Natal!\n";
        else
            cout << "Ho Ho Ho!\n";

    }

    return 0;
}