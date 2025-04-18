#include <algorithm>
#include <iostream>
#include <vector>

#define BAG_LIMIT 50

int packagesIncluded;

void knapsack(int packages, const std::vector <int>& weights, const std::vector<int>& quantities,
              std::vector<std::vector<int>> dp)
{
    for (int i = 1; i <= packages; ++i) // first row is always going to be only 0s (no packages were selected)
    {
        for (int w = 0; w <= BAG_LIMIT; ++w)
        {
            if (weights[i - 1] <= w)
            {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + quantities[i - 1]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtrack to find the relevant info
    int maxToys = 0;
    int totalWeight = 0;
    int packagesLeft = packages;

    int w = BAG_LIMIT;
    for (int i = packages; i > 0 && w > 0; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            totalWeight += weights[i - 1];
            maxToys += quantities[i - 1];
            --packagesLeft;
            w -= weights[i - 1];
        }
    }

    std::cout << maxToys << " brinquedos" << std::endl;
    std::cout << "Peso: " << totalWeight << " kg" << std::endl;
    std::cout << "sobra(m) " << packagesLeft << " pacote(s)" << std::endl;
    std::cout << std::endl;
}

int main() {
    int trips;
    std::cin >> trips;

    int packages;

    for (int i = 0; i < trips; ++i)
    {
        std::cin >> packages;
        std::vector<int> quantities(packages), weights(packages);
        std::vector<std::vector<int>> dpMatrix(packages + 1, (std::vector<int>(BAG_LIMIT + 1)));
        for (int j = 0; j < packages; ++j)
        {
            std::cin >> quantities[j] >> weights[j];
        }
        knapsack(packages, weights, quantities, dpMatrix);
    }
    return 0;
}