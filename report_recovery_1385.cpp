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
    parts.push_back(name);

    // total has as number of digits >= of each column
    int totalSelled = ceil((line.size() - i + 1) / columns);
    // cout << totalSelled << " " << (line.size() - i + 1) / columns << endl;
    string selled = line.substr(line.size() - totalSelled);
    cout << selled << endl;

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