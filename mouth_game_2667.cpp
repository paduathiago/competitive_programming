#include <iostream>
#include <string>

int main() {
    std::string gameNumber;
    std::cin >> gameNumber;

    unsigned sumOfDigits = 0;
    for (char& c : gameNumber)
    {
        sumOfDigits += c - '0';
    }

    std::cout << sumOfDigits % 3 << std::endl;
    /*It is possible to tell the % operation of a number by 3 using only the sum  of its digits*/

    return 0;
}