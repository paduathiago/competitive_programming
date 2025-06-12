#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, rev, capacity;
};

class Dinic {
public:
    vector<vector<Edge>> graph;
    vector<int> level, iter;

    Dinic(int n) : graph(n), level(n), iter(n) {}

    void addEdge(int from, int to, int capacity)
    {
        graph[from].push_back({to, (int)graph[to].size(), capacity});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0});
    }

    void bfs(int s)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;

        level[s] = 0;
        q.push(s);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (Edge &e : graph[v])
            {
                if (e.capacity > 0 && level[e.to] < 0)
                {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f)
    {
        if (v == t)
            return f;

        for (int &i = iter[v]; i < graph[v].size(); ++i)
        {
            Edge &e = graph[v][i];
            if (e.capacity > 0 && level[e.to] > level[v])
            {
                int d = dfs(e.to, t, min(f, e.capacity));
                if (d > 0)
                {
                    e.capacity -= d;
                    graph[e.to][e.rev].capacity += d;
                    return d;
                }
            }
        }

        return 0;
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        while (true)
        {
            bfs(s);
            if (level[t] < 0)
                return flow;

            fill(iter.begin(), iter.end(), 0);

            int f;
            while ((f = dfs(s, t, INT_MAX)) > 0)
                flow += f;
        }
    }
};

int main()
{
    int instance = 1;
    int nHorses, mSoldiers, kConections;

    while (cin >> nHorses >> mSoldiers >> kConections)
    {
        int totalNodes = nHorses + mSoldiers + 2;
        int source = 0, sink = totalNodes - 1;
        Dinic dinic(totalNodes);

        vector<int> horses(nHorses + 1);
        for (int i = 1; i <= nHorses; ++i)
        {
            cin >> horses[i];
            dinic.addEdge(mSoldiers + i, sink, horses[i]);
        }

        for (int i = 0; i < kConections; ++i)
        {
            int u, v; cin >> u >> v;
            dinic.addEdge(v, mSoldiers + u, 1);
        }

        for (int i = 1; i <= mSoldiers; ++i)
            dinic.addEdge(source, i, 1);

        int ans = dinic.max_flow(source, sink);
        cout << "Instancia " << instance++ << endl;
        cout << ans << endl;
    }

    return 0;
}