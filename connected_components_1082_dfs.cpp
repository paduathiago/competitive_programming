#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

std::vector<int> dfs(int root, std::vector<std::vector<int>>& adj)
{
    std::vector<bool> explored(adj.size(), false);
    std::vector<int> connectedGraph;
    std::stack<int> stack;

    stack.push(root);

    while(!stack.empty())
    {
        int vertice = stack.top();
        stack.pop();

        if(!explored[vertice])
        {
            explored[vertice] = true;
            connectedGraph.push_back(vertice);

            for (auto neighborsIt = adj[vertice].begin(); neighborsIt != adj[vertice].end(); ++neighborsIt)
            {
                if (!explored[*neighborsIt])
                {
                    stack.push(*neighborsIt);
                }
            }
        }
    }
    return connectedGraph;
}

int main() {
    int numberOfTetscases;
    int i, j;
    int vertices, edges;
    char connectedVertixA, connectedVertixB;

    std::cin >> numberOfTetscases;

    for (i = 0; i < numberOfTetscases; ++i)
    {
        std::cin >> vertices >> edges;

        std::vector<std::vector<int>> adj(vertices);

        for (j = 0; j < vertices; ++j)
        {
            adj[j].push_back(j);
        }

        for (j = 0; j < edges; ++j)
        {
            std::cin >> connectedVertixA >> connectedVertixB;
            adj[connectedVertixA - 'a'].push_back(connectedVertixB - 'a');
            adj[connectedVertixB - 'a'].push_back(connectedVertixA - 'a');
        }

        std::vector<bool> explored(vertices, 0);
        int countExplored = 0;
        int countSubgraphs = 0;
        std::cout << "Case #" << i + 1 << ":" << std::endl;
        int currentNode = 0;
        while(currentNode < vertices && countExplored < vertices)
        {
            if(!explored[currentNode])
            {
                std::vector<int> subgraph = dfs(currentNode, adj);
                std::sort(subgraph.begin(), subgraph.end());

                for (const auto& element : subgraph)
                {
                    explored[element] = true;
                    std::cout << static_cast<char>(element + 'a') << ",";
                }
                std::cout << std::endl;

                countExplored += subgraph.size();
                ++countSubgraphs;
            }
            ++currentNode;
        }
        std::cout << countSubgraphs << " connected components" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}