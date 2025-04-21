#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

int dijkstra(const vector<vector<pair<int, int>>>& graph, int origin, int destination)
{
    vector<int> dist(graph.size(), numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[origin] = 0;
    pq.push({0, origin});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == destination) break;
        if (current_dist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[destination];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int nIslands, mCables;
    cin >> nIslands >> mCables;

    vector<vector<pair<int, int>>> graph(nIslands);

    for (int i = 0; i < mCables; ++i)
    {
        int islandA, islandB, ping;
        cin >> islandA >> islandB >> ping;
        graph[islandA - 1].emplace_back(islandB - 1, ping);
        graph[islandB - 1].emplace_back(islandA - 1, ping);
    }

    int serverIsland;
    cin >> serverIsland;
    --serverIsland;

    int maxPing = 0;
    int minPing = numeric_limits<int>::max();

    for (int i = 0; i < nIslands; ++i)
    {
        if (i == serverIsland)
            continue;

        int currentPing = dijkstra(graph, i, serverIsland);
        minPing = min(minPing, currentPing);
        maxPing = max(maxPing, currentPing);
    }

    cout << maxPing - minPing << endl;

    return 0;
}