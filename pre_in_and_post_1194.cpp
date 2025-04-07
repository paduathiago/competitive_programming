#include <iostream>
#include <string>

std::string findPostOrder(std::string preOrder, std::string inOrder)
{
    if(preOrder.empty())
        return "";

    char root = preOrder[0];
    int inOrderRootIndex = inOrder.find(root);

    std::string leftInOrder = inOrder.substr(0, inOrderRootIndex);
    std::string rightInOrder = inOrder.substr(inOrderRootIndex + 1); // From the given element until the end of the string

    std::string leftPreOrder = preOrder.substr(1, leftInOrder.size());
    std::string rightPreOrder = preOrder.substr(1 + leftInOrder.size());

    std::string leftPostOrder = findPostOrder(leftPreOrder, leftInOrder);
    std::string rightPostOrder = findPostOrder(rightPreOrder, rightInOrder);

    return leftPostOrder + rightPostOrder + root;
}

int main() {
    int numberOfTests;
    std::cin >> numberOfTests;

    for (int i = 0; i < numberOfTests; ++i)
    {
        unsigned numberOfNodes;
        std::string preOrder, inOrder;
        std::cin >> numberOfNodes >> preOrder >> inOrder;

        std::cout << findPostOrder(preOrder, inOrder) << std::endl;
    }

    return 0;
}