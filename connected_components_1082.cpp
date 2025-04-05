#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>


int main() {
    int numberOfTetscases;
    int i, j;
    int vertices, edges;
    char connectedVertixA, connectedVertixB;

    std::cin >> numberOfTetscases;

    for (i = 0; i < numberOfTetscases; ++i)
    {
        std::vector<std::set<int>> subgraphs;

        std::cin >> vertices >> edges;
        std::vector<std::unordered_set<int>> adj(vertices);

        for (j = 0; j < vertices; ++j)
        {
            adj[j].insert(j);
        }

        for (j = 0; j < edges; ++j)
        {
            std::cin >> connectedVertixA >> connectedVertixB;
            adj[connectedVertixA - 97].insert(connectedVertixB - 97);
            adj[connectedVertixB - 97].insert(connectedVertixA - 97);
        }

        std::vector<bool> explored(vertices, 0);
        for (j = 0; j < std::max(edges, vertices); ++j)
        {
            if(explored[j])
                continue;

            std::set<int> subgraph;
            subgraph.insert(j);
            explored[j] = true;

            for (const auto& vertix : adj[j])
            {
                subgraph.insert(vertix);
                explored[vertix] = true;
                for (const auto& v : adj[vertix])
                {
                    subgraph.insert(v);
                }
            }
            subgraphs.push_back(subgraph);
        }

        std::cout << "Case #" << i + 1 << ":" << std::endl;
        for (const auto& subgraph: subgraphs)
        {
            for (const auto& element : subgraph)
                std::cout << static_cast<char>(element + 97) << ",";
            std::cout << std::endl;
        }
        std::cout << subgraphs.size() << " connected components" << std::endl;
        std::cout << std::endl;
    }
    return 0;
}