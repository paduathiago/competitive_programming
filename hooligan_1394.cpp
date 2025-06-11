#include <queue>
#include <map>
#include <cstring>
#include <climits>
#include <iostream>

using namespace std;

struct Edge {
    int from, to, capacity, flow;
    Edge() = default;
    Edge(int fr, int to, int cap, int fl = 0)
        : from(fr), to(to), capacity(cap), flow(fl) {}
};

class Dinic {
    static const int maxNodes = 1001;
    int source, sink, nodeCount;
    vector<int> adjacency[maxNodes];
    vector<Edge> edges;
    int distance[maxNodes];
    int pointer[maxNodes];

    bool bfs()
    {
        memset(distance, -1, sizeof(distance));
        queue<pair<int, int>> q;
        q.push({source, 0});
        distance[source] = 0;

        while (!q.empty()) {
            auto [u, d] = q.front();
            q.pop();

            if (u == sink)
                return true;

            for (int edgeId : adjacency[u])
            {
                const Edge& e = edges[edgeId];
                if (distance[e.to] != -1)
                    continue;
                if (e.capacity - e.flow > 0) {
                    distance[e.to] = d + 1;
                    q.push({e.to, d + 1});
                }
            }
        }
        return false;
    }

    int dfs(int u, int minCapacity) {
        if (u == sink) return minCapacity;

        for (int& i = pointer[u]; i < adjacency[u].size(); ++i) {
            int edgeId = adjacency[u][i];
            Edge& e = edges[edgeId];

            if (distance[e.to] != distance[u] + 1)
                continue;

            if (e.capacity - e.flow > 0)
            {
                int pushed = dfs(e.to, min(minCapacity, e.capacity - e.flow));
                if (pushed > 0)
                {
                    e.flow += pushed;
                    edges[edgeId ^ 1].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

public:
    void initialize(int _source, int _sink, int _nodeCount)
    {
        source = _source;
        sink = _sink;
        nodeCount = _nodeCount;

        for (int i = 0; i <= nodeCount; ++i)
            adjacency[i].clear();

        edges.clear();
    }

    void addEdge(int u, int v, int capacity)
    {
        adjacency[u].push_back(edges.size());
        edges.emplace_back(u, v, capacity);
        adjacency[v].push_back(edges.size());
        edges.emplace_back(v, u, 0);
    }

    int computeMaxFlow()
    {
        int maxFlow = 0;
        while (bfs())
        {
            memset(pointer, 0, sizeof(pointer));
            while (true)
            {
                int pushed = dfs(source, INT_MAX);
                if (!pushed) break;
                maxFlow += pushed;
            }
        }
        return maxFlow;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, g;
    while (cin >> n >> m >> g && n != 0) {
        int total[44] = {0};
        int played[44][44] = {0};
        map<pair<int, int>, int> nodeMap;

        for (int i = 0; i < g; ++i)
        {
            int u, v;
            char op;
            cin >> u >> op >> v;

            if (op == '>')
            {
                total[u] += 2;
            }
            else if (op == '=')
            {
                total[u]++;
                total[v]++;
            }
            else
            {
                total[v] += 2;
            }

            played[u][v]++;
            played[v][u]++;
        }

        int nodeCounter = 1;
        for (int i = 1; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                nodeMap[{i, j}] = nodeCounter++;
            }
        }
        for (int i = 1; i < n; ++i)
        {
            nodeMap[{i, i}] = nodeCounter++;
        }

        Dinic dinic;
        int source = 0;
        int sink = nodeCounter;
        dinic.initialize(source, sink, nodeCounter);

        for (int i = 1; i < n; ++i)
        {
            total[0] += (m - played[0][i]) * 2;
        }

        int sumExpected = 0;
        bool invalid = false;

        for (int i = 1; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int remaining = (m - played[i][j]) * 2;
                dinic.addEdge(source, nodeMap[{i, j}], remaining);
                dinic.addEdge(nodeMap[{i, j}], nodeMap[{i, i}], INT_MAX);
                dinic.addEdge(nodeMap[{i, j}], nodeMap[{j, j}], INT_MAX);
                sumExpected += remaining;
            }

            int allowed = total[0] - total[i] - 1;
            dinic.addEdge(nodeMap[{i, i}], sink, allowed);
            invalid = invalid || (allowed < 0);
        }

        int maxFlow = dinic.computeMaxFlow();

        if (!invalid && maxFlow == sumExpected)
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }

    return 0;
}