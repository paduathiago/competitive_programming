#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

int nCompetitors;
const int MAX = 610;
double M[MAX][MAX];
vector<int> tree[MAX];
double dp[MAX][MAX];
bool computed[MAX];

void dfs(int node)
{
    if (computed[node])
        return;

    computed[node] = true;

    if (node <= nCompetitors)
    {
        dp[node][node] = 1.0;
        return;
    }

    int left = tree[node][0];
    int right = tree[node][1];
    dfs(left);
    dfs(right);


    for (int i = 1; i <= nCompetitors; i++)
    {
        if (dp[left][i] == 0.0)
            continue;

        for (int j = 1; j <= nCompetitors; j++)
        {
            if (dp[right][j] == 0.0)
                continue;

            dp[node][i] += dp[left][i] * dp[right][j] * M[i][j];
            dp[node][j] += dp[right][j] * dp[left][i] * M[j][i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> nCompetitors, nCompetitors != 0)
    {
        int totalNodes = 2 * nCompetitors;

        for (int i = 1; i < totalNodes; i++)
        {
            tree[i].clear();
            computed[i] = false;
            fill(dp[i], dp[i] + nCompetitors + 1, 0.0);
        }

        for (int i = 1; i <= nCompetitors; i++)
        {
            for (int j = 1; j <= nCompetitors; j++)
                cin >> M[i][j];
        }

        vector<bool> isChild(2 * nCompetitors, false);

        for (int i = 1; i <= nCompetitors - 1; i++)
        {
            int A, B;
            cin >> A >> B;
            tree[nCompetitors + i].push_back(A);
            tree[nCompetitors + i].push_back(B);
            isChild[A] = true;
            isChild[B] = true;
        }

        int root = -1;
        for (int i = nCompetitors + 1; i < 2 * nCompetitors; i++)
        {
            if (!isChild[i])
            {
                root = i;
                break;
            }
        }

        dfs(root);
        cout << fixed << setprecision(6) << dp[root][1] << '\n';
    }

    return 0;
}
