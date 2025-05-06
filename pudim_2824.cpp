#include <iostream>
#include <string>
#include <vector>

using namespace std;

int longestCommonSubsequence(const string &search, const string &article)
{
    int n = search.size();
    int m = article.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (search[i-1] == article[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[n][m];
}

int main() {
    string seach, article;
    cin >> seach;
    cin >> article;

    cout << longestCommonSubsequence(seach, article) << endl;

    return 0;
}