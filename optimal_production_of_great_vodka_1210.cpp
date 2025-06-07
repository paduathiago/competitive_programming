#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int INF = std::numeric_limits<int>::max();

int nYears, iInitialAge, mMaxAge, pPrice;
vector<int> maintainanceCosts, salePrices;

int memo[2010][2010];
int nxt[2010][2010];

int dp(int time, int age)
{
    if(time == nYears + 1) return 0;

    int &p = memo[time][age];
    if(p != -1) return p;

    int sell = INF;
    int doNotSell = INF;

    sell = maintainanceCosts[0] + pPrice - salePrices[age] + dp(time + 1, 1);
    if(age < mMaxAge)
        doNotSell = maintainanceCosts[age] + dp(time + 1, age + 1);

    nxt[time][age] = sell <= doNotSell ? 1 : age + 1;

    return p = min(sell, doNotSell);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> nYears >> iInitialAge >> mMaxAge >> pPrice)
    {
        maintainanceCosts.resize(mMaxAge + 1);
        for (int i = 0; i < mMaxAge; ++i)
        {
            cin >> maintainanceCosts[i];
        }

        salePrices.resize(mMaxAge + 1);
        for (int i = 1; i <= mMaxAge; ++i)
        {
            cin >> salePrices[i];
        }

        for(int i = 0; i <= nYears; ++i)
        {
            for(int j = 0; j <= mMaxAge; ++j)
            {
                nxt[i][j] = 0;
                memo[i][j] = -1;
            }
        }

        cout << dp(1, iInitialAge) << endl;

        int t = 1, age = iInitialAge, flag = 0;
        do {
            if(nxt[t][age] == 1)
            {
                if(flag) cout << " ";
                flag = 1;
                cout << t;
            }

            age = nxt[t++][age];
        } while(t <= nYears);

        if(!flag)
            cout << 0;
        cout << endl;
    }

    return 0;
}