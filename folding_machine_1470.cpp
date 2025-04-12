#include <algorithm>
#include <iostream>
#include <vector>

bool isFoldedTapeTheOriginalReversed(const std::vector<unsigned>& tape, const std::vector<unsigned>& foldedTape)
{
    return std::equal(tape.begin(), tape.end(), foldedTape.rbegin());
}

unsigned newTapeSize(const int foldingPosition, int originalTapeSize)
{
    return std::max(foldingPosition, originalTapeSize - foldingPosition);
}

std::vector<unsigned> foldTape(const std::vector<unsigned>& tape, const int foldingPosition)
{
    int tapeSize = tape.size();
    std::vector<unsigned> foldedTape(newTapeSize(foldingPosition, tapeSize));
    // std::cout << "foldedTape size: " << foldedTape.size() << std::endl;

    int positionsFilled;

    if (foldingPosition < tapeSize / 2)
    {
        for (positionsFilled = 0; positionsFilled < abs(foldingPosition - (static_cast<int>(tapeSize) - foldingPosition)); ++positionsFilled)
        {
            foldedTape[positionsFilled] = tape[tapeSize - 1 - positionsFilled];
        }
    }

    // There will be elements left over on the right of the original tape (they won't be summed with any other element)
    else if (foldingPosition > tapeSize / 2 || (foldingPosition == tapeSize && tapeSize % 2 == 0))
    {
        for (positionsFilled = 0; positionsFilled < abs(foldingPosition - (static_cast<int>(tapeSize) - foldingPosition)); ++positionsFilled)
        {
            foldedTape[positionsFilled] = tape[positionsFilled];
        }
    }

    else // fold an even sized tape on its center
    {
        for (int i = 0; i < tapeSize / 2; ++i)
        {
            foldedTape[i] = tape[i] + tape[tapeSize - i - 1];
            return foldedTape;
        }
    }

    // std::cout << "positionsFilled: " << positionsFilled << std::endl;
    int j = 0;
    int k = positionsFilled;
    for (int i = positionsFilled; i < tapeSize; ++i)
    {
        foldedTape[i] = tape[j] + tape[k];
        --k;
        ++j;
        // std::cout << k << " " << j << std::endl;
    }

    // std::cout << "Folded tape: ";
    // for (unsigned element : foldedTape) {
    //     std::cout << element << " ";
    // }
    // std::cout << std::endl;
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
            int tapeElement;
            std::cin >> tapeElement;
            originalTape[i] = tapeElement;
        }

        std::cin >> foldedTapeSize;
        std::vector<unsigned> foldedTape(foldedTapeSize);
        for (unsigned i = 0; i < foldedTapeSize; ++i)
        {
            int tapeElement;
            std::cin >> tapeElement;
            foldedTape[i] = tapeElement;
        }

        std::cout << originalGeneratesFoldedTape(originalTape, foldedTape) << std::endl;
        // std::vector<unsigned> test = foldTape(originalTape, 2);
    }

    return 0;
}