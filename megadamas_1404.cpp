#include <iostream>
#include <algorithm>
#include <vector>

bool areCoordinatesValid(int rows, int columns, std::pair<int, int> coordinates)
{
    return coordinates.first >= 0 && coordinates.first < rows &&
           coordinates.second >= 0 && coordinates.second < columns;
}

// unsigned findBiggestNumberOfJumps(int rows, int columns, int board[rows][columns], std::pair<int, int> coordinates, bool isFirst = false)
// {
//     if (coordinates.first > rows - 1 || coordinates.first < 0 ||
//         coordinates.second > columns - 1 || coordinates.second < 0)
//         return 0;

//     if (!isFirst && board[coordinates.first][coordinates.second] != 0)
//         return 0;

//     // jump on left upper diagonal
//     int leftUpper = board[coordinates.first - 1][coordinates.second - 1] != 2 ||
//                     !areCoordinatesValid(rows, columns, std::make_pair(coordinates.first , coordinates.second)) ?
//                     0 :
//                     findBiggestNumberOfJumps(rows, columns, board[rows][columns],
//                     std::make_pair(--coordinates.first, --coordinates.second));  // avoid seg fault

//     // jump on left lower diagonal
//     int leftLower = findBiggestNumberOfJumps();

//     // jump on right upper diagonal
//     int rightUpper = findBiggestNumberOfJumps();

//     // jump on right lower diagonal
//     int rightLower = findBiggestNumberOfJumps();

//     if (isFirst)
//         return std::max({leftUpper, leftLower, rightUpper, rightLower});
//     else
//     {
//         return 1 + std::max({leftUpper, leftLower, rightUpper, rightLower})
//     }
// }

int main() {
    int rows, columns;

    while (std::cin >> rows >> columns && rows > 2 && columns > 2)
    {
        std::vector<std::vector<int>> board(rows, std::vector<int>(columns, 0));
        std::vector<std::pair<int, int>> myPieces;
        for (int i = rows - 1; i >= 0; --i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (i % 2 == 0)
                {
                    if(j % 2 == 1)
                        board[i][j] = -1;
                    else
                    {
                        std::cin >> board[i][j];
                        if (board[i][j] == 1)
                        {
                            myPieces.push_back(std::make_pair(i, j));
                        }
                    }
                }
                else
                {
                    if(j % 2 == 0)
                        board[i][j] = -1;
                    else
                    {
                        std::cin >> board[i][j];
                        if (board[i][j] == 1)
                        {
                            myPieces.push_back(std::make_pair(i, j));
                        }
                    }
                }
            }
        }


        // std::cout << findBiggestNumberOfJumps(rows, columns, board, myPieces[0], true) << std::endl;


        // print board
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
            std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}