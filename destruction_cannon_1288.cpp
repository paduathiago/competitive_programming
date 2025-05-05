#include <iostream>
#include <vector>

using namespace std;

void solveMission(unsigned nProjectiles, const vector<unsigned>& xDestructionPowers, const vector<unsigned>& yWeights, unsigned kCapacity, unsigned rResistance)
{
    vector<vector<unsigned>> dp(nProjectiles + 1, vector<unsigned>(kCapacity + 1, 0));

    for (unsigned i = 1; i <= nProjectiles; ++i)
    {
        for (unsigned j = 0; j <= kCapacity; ++j)
        {
            if (yWeights[i - 1] <= j)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - yWeights[i - 1]] + xDestructionPowers[i - 1]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    if (dp[nProjectiles][kCapacity] >= rResistance)
        cout << "Missao completada com sucesso";
    else
        cout << "Falha na missao";

    cout << endl;

}

int main() {
    unsigned missions, nProjectiles, kCapacity, rResistance;

    cin >> missions;
    for (unsigned i = 0; i < missions; ++i)
    {
        cin >> nProjectiles;

        vector<unsigned> xDestructionPowers(nProjectiles);
        vector<unsigned> yWeights(nProjectiles);

        for (unsigned j = 0; j < nProjectiles; ++j)
        {
            cin >> xDestructionPowers[j] >> yWeights[j];
        }

        cin >> kCapacity;
        cin >> rResistance;

        solveMission(nProjectiles, xDestructionPowers, yWeights, kCapacity, rResistance);
    }

    return 0;
}