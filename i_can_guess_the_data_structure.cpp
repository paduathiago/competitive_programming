#include <iostream>
#include <stack>
#include <queue>

int main() {
    int n, command, x;

    std::stack<int> stack;
    std::priority_queue<int> priorityQueue;
    std::queue<int> queue;

    int stackTop;
    int priorityFront;
    int queueFront;

    while (std::cin >> n)
    {
        bool isStack = true;
        bool isQueue = true;
        bool isPriorityQueue = true;
        bool isImpossible = false;
        int notSure = 0;

        stack = std::stack<int>();
        queue = std::queue<int>();
        priorityQueue = std::priority_queue<int>();

        for (int i = 0; i < n; ++i)
        {
            std::cin >> command >> x;
            if (command == 1)
            {
                stack.push(x);
                queue.push(x);
                priorityQueue.push(x);
            }

            else if (command == 2)
            {
                stackTop = stack.top();
                stack.pop();
                if (stackTop != x)
                {
                    isStack = false;
                }

                queueFront = queue.front();
                queue.pop();
                if (queueFront != x)
                {
                    isQueue = false;
                }

                priorityFront = priorityQueue.top();
                priorityQueue.pop();
                if (priorityFront != x)
                {
                    isPriorityQueue = false;
                }

                if (stackTop != x && queueFront != x && priorityFront != x)
                {
                    isImpossible = true;
                }
            }
        }
        notSure = isQueue + isStack + isPriorityQueue;

        if (isImpossible)
        {
            std::cout << "impossible" << std::endl;
        }
        else if (notSure > 1)
        {
            std::cout << "not sure" << std::endl;
        }
        else if (isStack)
        {
            std::cout << "stack" << std::endl;
        }
        else if (isQueue)
        {
            std::cout << "queue" << std::endl;
        }
        else if (isPriorityQueue)
        {
            std::cout << "priority queue" << std::endl;
        }
    }

    return 0;
}