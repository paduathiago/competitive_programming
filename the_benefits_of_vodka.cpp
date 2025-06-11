#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 1500, MAXM = 5e5, INF = 1e7;

int nTypes, mCategories;

class Dinic {
private:
    int ned, n;
    int first[MAXN], work[MAXN];
    int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

public:
    Dinic(int n) : n{n} {
        memset(first, -1, sizeof(int) * n);
        ned = 0;
    }

    void addEdge(int from, int toNode, int capacity)
    {
        to[ned] = toNode;
        cap[ned] = capacity;
        nxt[ned] = first[from];
        first[from] = ned++;
        to[ned] = from;
        cap[ned] = 0;
        nxt[ned] = first[toNode];
        first[toNode] = ned++;
    }

    int dfs(int current, int flow, int source, int sink)
    {
        if (current == sink)
            return flow;
        for (int& edge = work[current]; edge != -1; edge = nxt[edge])
        {
            int nextNode = to[edge];
            if (dist[nextNode] == dist[current] + 1 && cap[edge] > 0)
            {
                int pushed = dfs(nextNode, min(flow, cap[edge]), source, sink);
                if (pushed > 0)
                {
                    cap[edge] -= pushed;
                    cap[edge ^ 1] += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    bool bfs(int source, int sink)
    {
        memset(dist, -1, sizeof(int) * n);
        dist[source] = 0;
        queue<int> q;
        q.push(source);
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            for (int edge = first[current]; edge != -1; edge = nxt[edge])
            {
                int nextNode = to[edge];
                if (dist[nextNode] < 0 && cap[edge] > 0) {
                    dist[nextNode] = dist[current] + 1;
                    q.push(nextNode);
                }
            }
        }
        return dist[sink] >= 0;
    }

    int maxFlow(int source, int sink)
    {
        int totalFlow = 0;
        while (bfs(source, sink)) {
            memcpy(work, first, sizeof(int) * n);
            int flow;
            while ((flow = dfs(source, INF, source, sink)) > 0)
                totalFlow += flow;
        }
        return totalFlow;
    }
};


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    while (cin >> nTypes >> mCategories)
    {
        long long ans = 0;

        Dinic g(nTypes + mCategories + 2);
        vector<int> deg(mCategories);

        for(int i = 0; i < nTypes; ++i)
        {
            int p;
            cin >> p;
            g.addEdge(i, nTypes + mCategories + 1, p);
        }

        for(int& v : deg)
            cin >> v;

        for(int i = 0; i < mCategories; ++i)
        {
            int b;
            cin >> b;
            ans += b;
            g.addEdge(nTypes + mCategories, nTypes + i, b);
            for(int j = 0; j < deg[i]; ++j) {
                int id;
                cin >> id;
                g.addEdge(nTypes + i, id - 1, INF);
            }
        }
        cout << ans - g.maxFlow(nTypes + mCategories, nTypes + mCategories + 1) << endl;
    }

    return 0;
}