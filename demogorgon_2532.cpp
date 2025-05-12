#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    unsigned nSpells, hp;

    while (cin >> nSpells >> hp)
    {
        // First element is damage, second element is mana cost
        vector<pair<unsigned, unsigned>> spells(nSpells);

        for (unsigned i = 0; i < nSpells; ++i)
        {
            cin >> spells[i].first >> spells[i].second;
        }

        vector<unsigned> dp(hp + 1, UINT_MAX);
        dp[0] = 0;

        for (const auto& [Di, Mi] : spells)
        {
            for (int j = hp; j >= 0; --j)
            {
                if (dp[j] != UINT_MAX)
                {
                    int new_j = min(j + Di, hp);
                    if (new_j <= hp)
                    {
                        dp[new_j] = min(dp[new_j], dp[j] + Mi);
                    }
                }
            }
        }

        if (dp[hp] == UINT_MAX)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << dp[hp] << endl;
        }

    }

    return 0;
}