#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<char>> chessGrid;
vector<vector<int>> dist;
vector<vector<int>> visited;
vector<vector<int>> positionMap;
vector<vector<int>> dp;

int nRows, mCols, pPawns;

const int INF = std::numeric_limits<int>::max() / 2;

void bfs(int v, int x, int y)
{
    for (int i = 0; i < nRows; i++)
        fill(visited[i].begin(), visited[i].end(), 0);

    queue<pair<int, pair<int, int>>> q;
    q.push(make_pair(0, make_pair(x, y)));

    while (!q.empty())
    {
        pair<int, pair<int, int>> current = q.front();
        q.pop();
        int distance = current.first;
        int currX = current.second.first;
        int currY = current.second.second;

        if (currX < 0 || currY < 0 || currX >= nRows || currY >= mCols || chessGrid[currX][currY] == '#' )
            continue;

        if (visited[currX][currY])
            continue;

        visited[currX][currY] = 1;

        if (positionMap[currX][currY] != -1)
            dist[v][positionMap[currX][currY]] = distance;

        q.push(make_pair(distance + 1, make_pair(currX + 1, currY + 2)));
        q.push(make_pair(distance + 1, make_pair(currX + 1, currY - 2)));
        q.push(make_pair(distance + 1, make_pair(currX - 1, currY + 2)));
        q.push(make_pair(distance + 1, make_pair(currX - 1, currY - 2)));
        q.push(make_pair(distance + 1, make_pair(currX + 2, currY + 1)));
        q.push(make_pair(distance + 1, make_pair(currX + 2, currY - 1)));
        q.push(make_pair(distance + 1, make_pair(currX - 2, currY + 1)));
        q.push(make_pair(distance + 1, make_pair(currX - 2, currY - 1)));
    }
}

int tsp(int pos, int bitmask)
{
    if (dp[pos][bitmask] != -1)
        return dp[pos][bitmask];

    if (bitmask == (1 << (pPawns + 1)) - 1)
        return dp[pos][bitmask] = dist[pos][0];

    int ans = INF;
    for (int next = 0; next <= pPawns; next++)
    {
        if (next != pos && !(bitmask & (1 << next)))
            ans = min(ans, tsp(next, bitmask | (1 << next)) + dist[pos][next]);
    }
    return dp[pos][bitmask] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> nRows >> mCols >> pPawns && (nRows || mCols || pPawns))
    {
        chessGrid.resize(nRows, vector<char>(mCols));
        positionMap.resize(nRows, vector<int>(mCols, -1));
        visited.resize(nRows, vector<int>(mCols));

        int dpSize = pPawns + 1;
        int dpMask = 1 << (pPawns + 1);
        dp.assign(dpSize, vector<int>(dpMask, -1));
        dist.assign(dpSize, vector<int>(dpSize, INF));

        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < mCols; j++)
                cin >> chessGrid[i][j];
        }

        int pawnCount = 0;
        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < mCols; j++)
            {
                if (chessGrid[i][j] == 'P')
                    positionMap[i][j] = ++pawnCount;

                if (chessGrid[i][j] == 'C')
                    positionMap[i][j] = 0;
            }
        }

        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < mCols; j++)
            {
                if (positionMap[i][j] != -1)
                    bfs(positionMap[i][j], i, j);
            }
        }

        cout << tsp(0, 1) << endl;

        chessGrid.clear();
        positionMap.clear();
        visited.clear();
        dp.clear();
        dist.clear();
    }
    return 0;
}