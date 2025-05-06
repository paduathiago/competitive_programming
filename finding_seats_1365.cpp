#include <iostream>
#include <vector>
#include <climits>

using namespace std;

unsigned minimalExtension(const vector<vector<int>>& seats, int k)
{
    unsigned rows = seats.size();
    unsigned columns = seats[0].size();
    unsigned minExtension = UINT_MAX;

    vector<vector<int>> prefix(rows + 1, vector<int>(columns + 1, 0));

    for (unsigned i = 1; i <= rows; ++i)
    {
        for (unsigned j = 1; j <= columns; ++j)
        {
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + (seats[i-1][j-1] == 0);
            if (prefix[i][j] >= k)
            {
                minExtension = min(minExtension, i * j);
            }
        }
    }

    for (unsigned height = 1; height <= rows; ++height)
    {
        for (int i = 0; i + height <= rows; ++i)
        {
            unsigned left = 0;
            for (unsigned right = 0; right < columns; ++right)
            {
                int slidingWindowSeats = prefix[i+height][right+1] - prefix[i][right+1] - prefix[i+height][left] + prefix[i][left];
                while (slidingWindowSeats >= k) // shrink window size
                {
                    minExtension = min(minExtension, height * (right - left + 1));
                    ++left;
                    slidingWindowSeats = prefix[i + height][right + 1] - prefix[i][right + 1] - prefix[i + height][left] + prefix[i][left];
                }
            }
        }
    }

    return minExtension;
}

int main() {

    int kFriends, rows, columns;
    while (true)
    {
        cin >> rows >> columns >> kFriends;
        if (kFriends == 0 && rows == 0 && columns == 0)
            break;

        vector<vector<int>> seats(rows, vector<int>(columns, 0));
        char input;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cin >> input;
                if (input == 'X')
                {
                    seats[i][j] = 1; // occupied
                }
                else if (input == '.')
                {
                    seats[i][j] = 0; // empty
                }
            }
        }

        cout << minimalExtension(seats, kFriends) << endl;
    }

    return 0;
}