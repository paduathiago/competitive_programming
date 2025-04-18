#include <iostream>
#include <vector>

int main() {
    int nSwitches, mlamps;
    std::cin >> nSwitches >> mlamps;

    int L;
    std::cin >> L;
    std::vector<int> iluminated(L);
    for (int i = 0; i < L; ++i)
    {
         std::cin >>iluminated[i];
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
            lampsOfSwitch[i].push_back(lamp);
        }
    }

    for (int i = 0; i < nSwitches; ++i) {
        std::cout << "Switch " << i + 1 << ": ";
        for (int lamp : lampsOfSwitch[i]) {
            std::cout << lamp << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}