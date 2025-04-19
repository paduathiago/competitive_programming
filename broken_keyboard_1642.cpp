#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

int longestSubstringMKeys(const std::string phrase, const int mFunctionalKeys)
{
    int left = 0, right = 0;
    int maxLength = 0;
    std::unordered_map<char, int> charCount;

    while (right < static_cast<int>(phrase.length()))
    {
        ++charCount[phrase[right]];

        // shrink window if we have more items than functional keys
        while (static_cast<int>(charCount.size()) > mFunctionalKeys)
        {
            charCount[phrase[left]]--;
            if (charCount[phrase[left]] == 0)
            {
                charCount.erase(phrase[left]);
            }
            ++left;
        }
        maxLength = std::max(maxLength, right - left + 1);
        ++right;
    }

    return maxLength;
}

int main() {

    int mFunctionalKeys;
    std::string phrase;

    while (std::cin >> mFunctionalKeys && mFunctionalKeys != 0)
    {
        std::cin.ignore(); // Ignore the newline character after the integer input
        std::getline(std::cin, phrase);

        std::cout << longestSubstringMKeys(phrase, mFunctionalKeys) << std::endl;
    }

    return 0;
}