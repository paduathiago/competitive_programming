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
             std::string xxx = ""
             std::vector<std::vector<std::string>> brailleDigits;
             for (int i = 0; i < 2; ++i)
             {
                 for (int j = 0; j < digits; ++j)
                 {
                     std::string reading;
                     if (i == 0)
                     {
                          if (j % 2 == 0)
                          {
                              xxx = "";
                          }
                          std::cin >> reading;
                          xxx += reading;
                          if (j % 2 == 1) 
                          {
                              brailleDigits.pushback(xxx);
                          }
                     }
                     else if (i == 1)
                     {
                         std::cin >> reading;
                         brailleDigits[abs(j - 1) / 2] += reading;
                     }
                 }
             }
        }
    }

    return 0;
}
