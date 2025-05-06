#include <iostream>
#include <vector>

void solveGame(const std::vector<int>& game)
{
    std::vector<std::vector<int>> dp(game.size() + 1, std::vector<int>(game.size() + 1, 0));

    for (int i = 0; i < game.size(); ++i)
    {
        dp[i][i] = game[i] % 2 == 0 ? 1 : 0;
    }

    for (int len = 2; len <= game.size(); ++len)
    {
        for (int i = 0; i <= game.size() - len; ++i)
        {
            int j = i + len - 1;
            if ((game.size() - len) % 2 == 0) // First player's turn
            {
                int pickLeft = (game[i] % 2 == 0) ? 1 : 0;
                int pickRight = (game[j] % 2 == 0) ? 1 : 0;
                dp[i][j] = std::max(pickLeft + dp[i+1][j], pickRight + dp[i][j-1]);
            }
            else  // Second player's turn
            {
                dp[i][j] = std::min(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    int firstPlayerScore = dp[0][game.size() - 1];
    std::cout << firstPlayerScore << std::endl;
}

int main() {
    int nNumber;

    while(std::cin >> nNumber && nNumber!= 0)
    {
        std::vector<int> game(2 *nNumber);
        for (int i = 0 ; i < 2 * nNumber; ++i)
        {
            std::cin >> game[i];
        }
        solveGame(game);
    }

    return 0;
}