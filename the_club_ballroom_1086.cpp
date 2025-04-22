#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int solve(int required_length, vector<int>& planks, int rowsNeeded) {
    int left = 0, right = planks.size() - 1;
    int count = 0, filled = 0;

    while (left < right)
    {
        if (planks[right] > required_length)
        {
            --right;
        }
        else if (planks[right] == required_length)
        {
            ++filled;
            ++count;
            --right;
        }
        else
        {
            if (planks[left] + planks[right] == required_length)
            {
                ++filled;
                count += 2;
                ++left;
                --right;
            }

            else if ((planks[left] + planks[right] > required_length))
            {
                --right;
            }

            else
            {
                ++left;
            }
        }

        if (filled == rowsNeeded)
        {
            return count;
        }
    }

    if (left == right)
    {
        if (planks[right] == required_length)
        {
            ++filled;
            ++count;
        }
        if (filled == rowsNeeded)
        {
            return count;
        }
    }

    return numeric_limits<int>::max();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N, L, K;

    while (cin >> M >> N, M || N)
    {
        cin >> L >> K;
        vector<int> planks(K);

        for (int i = 0; i < K; ++i)
        {
            cin >> planks[i];
        }

        sort(planks.begin(), planks.end()); // Sort in ascending order

        int min_planks = numeric_limits<int>::max();
        bool possible = false;

        // Case 1: Planks parallel to N (length N)
        if ((M * 100) % L == 0)
        {
            int rows_needed = (M * 100) / L;
            int planks_needed = solve(N, planks, rows_needed);
            min_planks = min(min_planks, planks_needed);
            possible = min_planks != numeric_limits<int>::max();
        }

        // Case 2: Planks parallel to M (length M)
        if ((N * 100) % L == 0)
        {
            int rows_needed = (N * 100) / L;
            int planks_needed = solve(M, planks, rows_needed);
            min_planks = min(min_planks, planks_needed);
            possible = possible || (min_planks != numeric_limits<int>::max());
        }

        if (possible)
        {
            cout << min_planks << endl;
        }
        else
        {
            cout << "impossivel" << endl;
        }
    }

    return 0;
}