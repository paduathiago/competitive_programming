#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

int  splitHeader(const string& line)
{
    vector<string> parts;
    string part;
    for (char ch : line)
    {
        if (ch == 'P')
        {
            if (!part.empty())
            {
                parts.push_back(part);
                part.clear();
            }
        }
        else if (ch == 'T')
        {
            parts.push_back(part);
            for (const string& p : parts)
            {
                cout << p << " ";
            }
            cout << "Totals" << endl;
            break;
        }
        part += ch;
    }
    return parts.size() + 1;
}

int sumSlices(const vector<string>& slices)
{
    int total = 0;
    for (const string& slice : slices)
    {
        total += slice.size();
    }
    return total;
}

vector<string> divideSubString(string str, int columns)
{
    vector<string> parts;
    vector<int> markers;
    int partSize = ceil(static_cast<double>(str.size()) / columns);

    int markerPosition = str.size() - partSize;
    while (markerPosition > 0)
    {
        markers.push_back(markerPosition);
        markerPosition -= partSize;
    }

    vector<string> slices(columns);
    slices[0] = str.substr(0, markers[markers.size() - 1]);
    for (int i = markers.size() - 1; i > 0; --i)
    {
        slices[i] = str.substr(markers[i], markers[i - 1] - markers[i]);
    }
    slices[columns - 1] = str.substr(markers[0], str.size() - markers[0]);

    for (int i = 0; i < columns; ++i) // REMOVE
    {
        cout << slices[i] << " ";
    }
    return slices;
}

vector<string> splitSellerLine(const string& line, int columns)
{
    vector<string> parts;
    int i = 0;

    // Extract seller name (alphabetic characters)
    string name;
    while (i < line.size() && isalpha(line[i]))
    {
        name += line[i];
        ++i;
    }
    cout << name << " ";

    // total has as number of digits >= of each column
    int totalSelled = ceil(static_cast<double>(line.size() - i) / columns);
    string selled = line.substr(line.size() - totalSelled);
    // cout << selled << endl;

    // consider passing the entire string to divideSubString
    int remainingStringSize = line.size() - i - totalSelled;
    string remainingString = line.substr(i, remainingStringSize);
    auto slices = divideSubString(remainingString, columns - 1);
    cout << endl;

    return parts;
}


void processTestCase()
{
    string header;
    getline(cin, header);
    int columns = splitHeader(header);

    vector<vector<string>> sellerLines;
    string line;
    while (true)
    {
        getline(cin, line);
        if (line.substr(0, 2) == "TP")
        {
            break;
            // TODO
        }
        sellerLines.push_back(splitSellerLine(line, columns));
    }
    // vector<string> totalsLine = splitTotalsLine(line, columns);
}

int main() {
    int cTests;
    cin >> cTests;
    cin.ignore();

    for (int i = 0; i < cTests; ++i)
    {
        processTestCase();
    }

    return 0;
}