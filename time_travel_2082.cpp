#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 1e9;
const int MAXN = 110;

int graph[MAXN][MAXN];

int stoerWagner(int n)
{
    vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = i;
    int minCut = INF;

    while (n > 1)
    {
        vector<int> w(n, 0);
        int prev = 0, last = 0;
        vector<bool> added(n, false);

        for (int i = 0; i < n; ++i)
        {
            int sel = -1;
            for (int j = 0; j < n; ++j)
            {
                if (!added[j] && (sel == -1 || w[j] > w[sel]))
                    sel = j;
            }

            if (i == n - 1)
            {
                minCut = min(minCut, w[sel]);
                // Merge sel into prev
                for (int j = 0; j < n; ++j)
                {
                    graph[v[prev]][v[j]] += graph[v[sel]][v[j]];
                    graph[v[j]][v[prev]] += graph[v[j]][v[sel]];
                }
                v.erase(v.begin() + sel);
                --n;
                break;
            }
            added[sel] = true;
            prev = last;
            last = sel;
            for (int j = 0; j < n; ++j)
                if (!added[j])
                    w[j] += graph[v[sel]][v[j]];
        }
    }
    return minCut;
}

int main() {
    int tests;
    cin >> tests;

    while (tests--)
    {
        int nMachines, mConnections;
        cin >> nMachines >> mConnections;
        memset(graph, 0, sizeof(graph));

        for (int i = 0; i < mConnections; ++i)
        {
            int u, v, cost;
            cin >> u >> v >> cost;
            --u; --v;
            graph[u][v] += cost;
            graph[v][u] += cost;
        }

        cout << stoerWagner(nMachines) << endl;
    }
    return 0;
}