#include <iostream>
#include <vector>
#include <queue>
#include <map>
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    map<string, int> sizeMap = {
        {"XS", 0}, {"S", 1}, {"M", 2}, {"L", 3}, {"XL", 4}, {"XXL", 5}
    };

    int tests;
    cin >> tests;

    int nShirts, mVolunteers;
    while (tests--)
    {
        cin >> nShirts >> mVolunteers;

        int shirtsPerSize = nShirts / 6;

        int V = 1 + 1 + mVolunteers + 6; // source + sink + volunteers + sizes
        int source = 0, sink = V - 1;
        int firstVolunteer = 1;
        int firstSize = 1 + mVolunteers;

        Dinic dinic(V);

        for (int i = 0; i < mVolunteers; ++i)
            dinic.addEdge(source, firstVolunteer + i, 1);

        for (int i = 0; i < 6; ++i)
            dinic.addEdge(firstSize + i, sink, shirtsPerSize);

        for (int i = 0; i < mVolunteers; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            dinic.addEdge(firstVolunteer + i, firstSize + sizeMap[s1], 1);
            dinic.addEdge(firstVolunteer + i, firstSize + sizeMap[s2], 1);
        }

        int flow = dinic.max_flow(source, sink);
        cout << (flow == mVolunteers ? "YES" : "NO") << endl;
    }


    return 0;
}