#include <iostream>
#include <vector>

using namespace std;

int main() {
    unsigned nColumns;

    cin >> nColumns;

    vector<unsigned> aHeights(nColumns);

    for (unsigned i = 0; i < nColumns; ++i)
    {
        cin >> aHeights[i];
    }

    unsigned maxHeight = 0;

    vector<unsigned> left(nColumns);
    vector<unsigned> right (nColumns);

    left[0] = 1;
    right[nColumns - 1] = 1;

    for (unsigned i = 1; i < nColumns; ++i)
    {
        left[i] = min(left[i - 1] + 1, aHeights[i]);
    }

    for (int j = nColumns - 2; j >= 0; --j)
    {
        right[j] = min(right[j + 1] + 1, aHeights[j]);
        maxHeight = max(maxHeight, min(right[j], left[j]));
    }

    cout << maxHeight << endl;

    return 0;
}