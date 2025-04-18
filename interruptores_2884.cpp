#include <bitset>
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
    int nSwitches, mlamps;
    std::cin >> nSwitches >> mlamps;

    int L;
    std::cin >> L;
    std::bitset<1000> illuminated;
    for (int i = 0; i < L; ++i)
    {
        int lit;
        std::cin >> lit;
        illuminated.set(lit - 1);
    }

    int K;
    std::vector<std::vector<int>> lampsOfSwitch(nSwitches);
    for (int i = 0; i < nSwitches; ++i)
    {
        std::cin >> K;
        for (int j = 0; j < K; ++j)
        {
            int lamp;
            std::cin >> lamp;
            lampsOfSwitch[i].push_back(lamp - 1);
        }
    }

    int switchesPressed = 0;
    int nextToPress = 0;
    std::unordered_set<std::bitset<1000>> visited;
    while (!illuminated.none())
    {
        if (switchesPressed % nSwitches == 0 && visited.find(illuminated) != visited.end())
        {
            std::cout << -1 << std::endl;
            return 0;
        }

        visited.insert(illuminated);
        for (const int & lamp : lampsOfSwitch[nextToPress])
        {
            illuminated.flip(lamp);
        }

        ++switchesPressed;
        nextToPress = (nextToPress + 1) % nSwitches;
    }
    std::cout << switchesPressed << std::endl;

    return 0;
}