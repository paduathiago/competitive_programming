#include <algorithm>
#include <iostream>
#include <vector>

bool isFoldedTapeTheOriginalReversed(const std::vector<unsigned>& tape, const std::vector<unsigned>& foldedTape)
{
    return std::equal(tape.begin(), tape.end(), foldedTape.rbegin());
}

std::vector<unsigned> foldTape(const std::vector<unsigned>& tape, const int foldingPosition)
{
    int tapeSize = tape.size();
    int left = foldingPosition;
    int right = tapeSize - foldingPosition;
    std::vector<unsigned> foldedTape(std::max(left, right));

    if (left <= right)
    {
        int i = tapeSize - 1;
        int j = 0;
        int k = right - left;
        while (k > 0)
        {
            foldedTape[j] = tape[i];
            --i;
            ++j;
            --k;
        }
        while (k < i)
        {
            foldedTape[j] = tape[k] + tape[i];
            --i;
            ++k;
            ++j;
        }
    }
    else
    {
        int i = 0;
        while (i < left - right)
        {
            foldedTape[i] = tape[i];
            ++i;
        }

        int k = tapeSize - 1;
        while (i < k)
        {
            foldedTape[i] = tape[i] + tape[k];
            ++i;
            --k;
        }
    }

    return foldedTape;

}

char originalGeneratesFoldedTape(const std::vector<unsigned>& tape, const std::vector<unsigned>& foldedTape)
{
    if (tape.size() < foldedTape.size())
        return 'N';

    if (tape.size() == foldedTape.size())
    {
        if (tape == foldedTape)
            return 'S';

        if (isFoldedTapeTheOriginalReversed(tape, foldedTape))
            return 'S';

        return 'N';
    }

    for (int i = 1; i < static_cast<int>(tape.size()); ++i)  // index 0 means reversing
    {
        std::vector<unsigned> newTape = foldTape(tape, i);
        if (originalGeneratesFoldedTape(newTape, foldedTape) == 'S')
            return 'S';
    }
    return 'N';
}

int main() {
    unsigned originalTapeSize, foldedTapeSize;

    while (std::cin >> originalTapeSize)
    {
        std::vector<unsigned> originalTape(originalTapeSize);
        for (unsigned i = 0; i < originalTapeSize; ++i)
        {
            std::cin >> originalTape[i];
        }

        std::cin >> foldedTapeSize;
        std::vector<unsigned> foldedTape(foldedTapeSize);
        for (unsigned i = 0; i < foldedTapeSize; ++i)
        {
            std::cin >> foldedTape[i];
        }

        std::cout << originalGeneratesFoldedTape(originalTape, foldedTape) << std::endl;
    }

    return 0;
}