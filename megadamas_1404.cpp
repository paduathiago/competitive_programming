#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

bool areDirCoordinatesValid(const int rows, const int columns, const int dirX, const int dirY)
{
    return dirX >= 0 && dirX < rows &&
           dirY >= 0 && dirY < columns;
}

struct State
{
    int row, col;
    unsigned jumps;
    int prevDir;
    std::vector<std::pair<int, int>> captured;
};

unsigned maxJumps(int rows, int columns, std::vector<std::vector<int>> board, std::pair<int, int> start)
{
    std::stack<State> stack;
    stack.push ({start.first, start.second, 0, -1, {}});

    unsigned maxJumps = 0;

    while (!stack.empty())
    {
        State currentState = stack.top();
        stack.pop();

        maxJumps = std::max(maxJumps, currentState.jumps);

        for (int dir = 1; dir <= 4; ++dir)
        {

            int dx1, dy1, dx2, dy2;
            switch (dir)
            {
                case 1: if (currentState.prevDir == 4) continue; dx1 = -1; dy1 = -1; dx2 = -2; dy2 = -2; break;
                case 2: if (currentState.prevDir == 3) continue; dx1 = 1;  dy1 = -1; dx2 = 2;  dy2 = -2; break;
                case 3: if (currentState.prevDir == 2) continue; dx1 = -1; dy1 = 1;  dx2 = -2; dy2 = 2;  break;
                case 4: if (currentState.prevDir == 1) continue; dx1 = 1;  dy1 = 1;  dx2 = 2;  dy2 = 2;  break;
            }

            if (!areDirCoordinatesValid(rows, columns, currentState.row + dx2, currentState.col + dy2))
                continue;

            // board[currentState.row + dx1][currentState.col + dy1] is the piece (position) jumped over
            if (board[currentState.row + dx1][currentState.col + dy1] != 2)
                continue;

            if (board[currentState.row + dx2][currentState.col + dy2] != 0)
                continue;

            if (std::find(currentState.captured.begin(), currentState.captured.end(),
                          std::make_pair(currentState.row + dx1, currentState.col + dy1))
                          != currentState.captured.end())
                continue;

            auto newCaptured = currentState.captured;
            newCaptured.push_back(std::make_pair(currentState.row + dx1, currentState.col + dy1));

            stack.push({currentState.row + dx2, currentState.col + dy2, currentState.jumps + 1, dir,
                           newCaptured});
        }
    }
    return maxJumps;
}


int main() {
    int rows, columns;

    while (std::cin >> rows >> columns && rows > 2 && columns > 2)
    {
        std::vector<std::vector<int>> board(rows, std::vector<int>(columns, 0));
        std::vector<std::pair<int, int>> myPieces;
        int k = 0;
        for (int i = rows - 1; i >= 0; --i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (k % 2 == 0)
                {
                    if(j % 2 == 1)
                    {
                        board[i][j] = -2;
                        continue;
                    }
                }
                else
                {
                    if(j % 2 == 0)
                    {
                        board[i][j] = -2;
                        continue;
                    }
                }
                std::cin >> board[i][j];
                if (board[i][j] == 1)
                {
                    myPieces.push_back(std::make_pair(i, j));
                }
            }
            ++k;
        }

        unsigned maxCaptures = 0;
        for (const auto& piece : myPieces)
        {
            unsigned jumps = maxJumps(rows, columns, board, piece);
            if (jumps > maxCaptures)
                maxCaptures = jumps;
        }
        std::cout << maxCaptures << std::endl;
    }

    return 0;
}