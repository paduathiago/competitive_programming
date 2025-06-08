#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
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

    int nAirports, mFlights, aAthletes;
    int oOrigin, dDestination, sSeats;

    vector<tuple<int, int, int>> flights;

    while (cin >> nAirports >> mFlights >> aAthletes)
    {
        if (nAirports == 0 && mFlights == 0 && aAthletes == 0) break;
        flights.clear();

        for (int i = 0; i < mFlights; ++i)
        {
            cin >> oOrigin >> dDestination >> sSeats;
            flights.emplace_back(oOrigin - 1, dDestination - 1, sSeats);
        }

        int low = 1, high = aAthletes * 2, answer = aAthletes * 2;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            int totalNodes = nAirports * (mid + 1);
            Dinic dinic(totalNodes + 2);
            int source = totalNodes, sink = totalNodes + 1;

            dinic.addEdge(source, 0, aAthletes);

            int node = mid * nAirports + (nAirports - 1);
            dinic.addEdge(node, sink, aAthletes);

            for (int d = 0; d < mid; ++d)
            {
                for (int a = 0; a < nAirports; ++a)
                {
                    int from = d * nAirports + a;
                    int to = (d + 1) * nAirports + a;
                    dinic.addEdge(from, to, aAthletes);
                }
            }

            for (const auto &flight : flights)
            {
                int O = get<0>(flight);
                int D = get<1>(flight);
                int S = get<2>(flight);
                for (int d = 0; d < mid; ++d)
                {
                    int from = d * nAirports + O;
                    int to = (d + 1) * nAirports + D;
                    dinic.addEdge(from, to, S);
                }
            }

            int flow = dinic.max_flow(source, sink);
            if (flow >= aAthletes)
            {
                answer = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        cout << answer << endl;

    }

    return 0;
}