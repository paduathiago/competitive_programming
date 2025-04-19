#include <cstddef>
#include <iostream>
#include <string>

int main() {
    std::string enigma, crib;
    std::cin >> enigma;
    std::cin >> crib;

    unsigned countMatches = 0;

    for (size_t i = 0; i + crib.length() - 1 < enigma.length(); ++i)
    {
        int k = i;
        bool match = true;
        for (size_t j = 0; j < crib.length(); ++j)
        {
            if (enigma[k] == crib[j])
            {
                match = false;
                break;
            }
            ++k;
        }
        if (match)
            ++countMatches;
    }

    std::cout << countMatches << std::endl;

    return 0;
}