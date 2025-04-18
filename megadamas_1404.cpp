#include <iostream>
#include <vector>

std::vector<std::vector<bool>> captured;
int maxCaptures;

bool areCoordinatesValid(const int rows, const int columns, const int dirX, const int dirY)
{
    return dirX >= 0 && dirX < rows &&
           dirY >= 0 && dirY < columns;
}

void maxJumps(const int rows, const int columns, std::vector<std::vector<int>>& board,
              const std::pair<int, int> start, int current_captures)
{
    bool found = false;
    for (int dir = 0; dir < 4; ++dir)
    {

        int dx1, dy1, dx2, dy2;
        switch (dir)
        {
            case 0: dx1 = -1; dy1 = -1; dx2 = -2; dy2 = -2; break;
            case 1: dx1 = -1; dy1 = 1;  dx2 = -2; dy2 = 2;  break;
            case 2: dx1 = 1;  dy1 = -1; dx2 = 2;  dy2 = -2; break;
            case 3: dx1 = 1;  dy1 = 1;  dx2 = 2;  dy2 = 2;  break;
        }

        int nx = start.first + dx1;
        int ny = start.second + dy1;
        int nx2 = start.first + dx2;
        int ny2 = start.second + dy2;

        if (areCoordinatesValid(rows, columns, nx2, ny2))
        {
            if (board[nx][ny] == 2 && board[nx2][ny2] == 0 && !captured[nx][ny])
            {
                captured[nx][ny] = true;
                int originalValue = board[start.first][start.second];
                board[start.first][start.second] = 0;
                int temp = board[nx2][ny2];
                board[nx2][ny2] = 1;
                maxJumps (rows, columns, board, std::make_pair(nx2, ny2), current_captures + 1);
                board[start.first][start.second] = originalValue;
                board[nx2][ny2] = temp;
                captured[nx][ny] = false;
                found = true;
            }
        }
    }
    if (!found)
    {
        if (current_captures > maxCaptures)
            maxCaptures = current_captures;
    }
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
                    myPieces.push_back(std::make_pair(i, j));
            }
            ++k;
        }

        maxCaptures = 0;
        for (const auto& piece : myPieces)
        {
            captured.assign(rows, std::vector<bool>(columns, false));
            maxJumps(rows, columns, board, piece, 0);
        }
        std::cout << maxCaptures << std::endl;
    }

    return 0;
}