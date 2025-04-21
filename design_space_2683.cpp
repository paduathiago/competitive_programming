#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge& other) const
    {
        return w < other.w;
    }
};

vector<int> parent;

int find(int u)
{
    if (parent[u] != u)
        parent[u] = find(parent[u]);

    return parent[u];
}

long long kruskal(vector<Edge>& edges, int n, bool minTree)
{
    parent.resize(n+1);
    for (int i = 1; i <= n; i++) parent[i] = i;

    if (!minTree)
        sort(edges.rbegin(), edges.rend());
    else
        sort(edges.begin(), edges.end());

    long long total = 0;
    int count = 0;

    for (const Edge& e : edges)
    {
        int rootU = find(e.u);
        int rootV = find(e.v);
        if (rootU != rootV)
        {
            parent[rootV] = rootU;
            total += e.w;
            if (++count == n-1) break;
        }
    }
    return total;
}

int main() {
    int N;
    cin >> N;
    vector<Edge> edges(N);
    int maxNode = 0;

    for (int i = 0; i < N; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        maxNode = max(maxNode, max(edges[i].u, edges[i].v));
    }

    long long minCost = kruskal(edges, maxNode, true);
    long long maxCost = kruskal(edges, maxNode, false);

    cout << maxCost << endl << minCost << endl;

    return 0;
}