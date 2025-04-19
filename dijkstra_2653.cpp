#include <iostream>
#include <unordered_set>
#include <string>

int main() {

    std::string gem;
    std::unordered_set<std::string> gems;

    while (std::cin >> gem)
    {
        gems.insert(gem);
    }

    std::cout << gems.size() << std::endl;

    return 0;
}