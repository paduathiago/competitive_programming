#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

double maxExpectedPrize(const vector<unsigned>& pPrizes, const vector<float>& cChances, unsigned kSkips)
{
    vector<double> next(kSkips + 1, 0.0), current(kSkips + 1, 0.0);

    for (int i = pPrizes.size() - 1; i >= 0; --i)
    {
        for (unsigned j = 0; j <= kSkips; ++j)
        {
            double answerQuestion = cChances[i] * (pPrizes[i] + next[j]);
            double skipQuestion = (j > 0) ? pPrizes[i] + next[j - 1] : 0.0;
            current[j] = max(answerQuestion, skipQuestion);
        }
        swap(current, next);
    }

    return next[kSkips];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned nQuestions, kSkips;
    int chance;
    while (cin >> nQuestions >> kSkips)
    {
        vector <unsigned> pPrizes(nQuestions);
        for (unsigned i = 0; i < nQuestions; ++i)
        {
            cin >> pPrizes[i];
        }

        vector<float> cChances(nQuestions);
        for (unsigned i = 0; i < nQuestions; ++i)
        {
            cin >> chance;
            cChances[i] = chance / 100.0;
        }

        cout << fixed << setprecision(2) << maxExpectedPrize(pPrizes, cChances, kSkips) << endl;
    }
    return 0;
}