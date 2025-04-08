#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


int main() {

    std::unordered_map<std::string, char> brailleToDigit = {
        {"*...", '1'},
        {"*.*.", '2'},
        {"**..", '3'},
        {"**.*", '4'},
        {"*..*", '5'},
        {"***.", '6'},
        {"****", '7'},
        {"*.**", '8'},
        {".**.", '9'},
        {".***", '0'}
    };

    std::unordered_map<char, std::vector<std::string>> digitToBraille = {
        {'1', {"*.", "..", ".."}},
        {'2', {"*.", "*.", ".."}},
        {'3', {"**", "..", ".."}},
        {'4', {"**", ".*", ".."}},
        {'5', {"*.", ".*", ".."}},
        {'6', {"**", "*.", ".."}},
        {'7', {"**", "**", ".."}},
        {'8', {"*.", "**", ".."}},
        {'9', {".*", "*.", ".."}},
        {'0', {".*", "**", ".."}}
    };

    unsigned digits = 101;
    while(digits > 0)
    {
        std::cin >> digits;

        char sOrB;
        std::cin >> sOrB;

        if(sOrB == 'S')
        {
            std::string number;
            std::cin >> number;

            std::vector<std::vector<std::string>> brailleFromNumbers;

            for(const char& digit : number)
            {
                brailleFromNumbers.push_back(digitToBraille[digit]);
            }
            for (int i = 0; i < 3; ++i)
            {
                for (std::size_t j = 0; j < brailleFromNumbers.size(); ++j)
                {
                    std::cout << brailleFromNumbers[j][i];
                    if (j != brailleFromNumbers.size() - 1) // Check if it's not the last element
                    {
                        std::cout << " ";
                    }
                }
                std::cout << std::endl;
            }
        }

         else if(sOrB == 'B')
         {
             std::string reading;
             std::vector<string> brailleDigits;
             for (int i = 0; i < 3; ++i)
             {
                 for (int j = 0; j < digits; ++j)
                 {
                     if (i == 0)
                     {
                          std::cin >> reading;
                          brailleDigits.pushback(reading);
                     }
                     else if (i == 1)
                     {
                         std::cin >> reading;
                         brailleDigits[j] += reading;
                     }
                     else
                     {
                         std::cin >> reading;
                     }
                 }
             }
             
             for(size_t i = 0; i < brailleDigits.size; ++i)
             {
                 std::cout << brailleToDigit[brailleDigits[i]];
             }
             std::cout << std::endl;
        }
    }

    return 0;
}
