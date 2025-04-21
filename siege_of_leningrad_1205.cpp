#include <iostream>
#include <limits>
#include <vector>

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int origin, int destination)
{
    --origin;
    --destination;

    std::vector<bool> unvisited(graph.size(), 1);
    int visited = 0;

    std::vector<int> previousNode(graph.size(), -1);

    std::vector<int> shortestDistance(graph.size(), std::numeric_limits<int>::max());
    shortestDistance[origin] = 0;

    int currentNode = origin;
    while (visited < static_cast<int>(graph.size()))
    {
        unvisited[currentNode] = false;
        ++visited;
        int minDistance = std::numeric_limits<int>::max();
        int nextNode = -1;
        for (const auto& edge: graph[currentNode])
        {
            if (edge.second + shortestDistance[currentNode] < shortestDistance[edge.first])
            {
                shortestDistance[edge.first] = edge.second + shortestDistance[currentNode];
                previousNode[edge.first] = currentNode;
            }
            if (shortestDistance[edge.first] < minDistance && unvisited[edge.first])
            {
                minDistance = shortestDistance[edge.first];
                nextNode = edge.first;
                if (minDistance < shortestDistance[nextNode])
                    previousNode[nextNode] = currentNode;
            }
        }
        currentNode = nextNode;
    }

    // Now we backtrack from the destination to find the shortest path
    std::vector<int> shortestPath;

    int nextNodePath = destination;
    shortestPath.emplace_back(destination);

    while(nextNodePath != origin)
    {
        shortestPath.emplace_back(previousNode[nextNodePath]);
        nextNodePath = previousNode[nextNodePath];
    }

    return shortestPath;
}

float probabilityOfPoint(int snipersOnPoint, int kBullets, float pProbability)
{
    if (snipersOnPoint == 0)
        return 1.0f;

    float probability = 1.0f;
    for (int i = 0; i < snipersOnPoint; ++i)
    {
        probability *= (1 - pProbability);
    }

    for (int i = 0; i < kBullets; ++i)
    {
        probability *= pProbability;
    }

    return probability;
}

int main() {
    int nStrategicPoints, mRoads, kBullets;
    float pProbability;

    int iRoad, jRoad;
    std::vector<std::pair<int, int>> edges;

    int aSnipers, sniperOnPoint;
    int origin, destination;

    while (std::cin >> nStrategicPoints >> mRoads >> kBullets >> pProbability)
    {
        // pair.first = destination node
        // pair.second = edge weight
        std::vector<std::vector<std::pair<int, int>>> graph(nStrategicPoints);

        std::vector<int> snipersOnPoint(nStrategicPoints, 0);

        for (int i = 0; i < mRoads; ++i)
        {
            std::cin >> iRoad >> jRoad;
            edges.emplace_back(std::make_pair(iRoad, jRoad));
        }

        std::cin >> aSnipers;
        for (int i = 0; i < aSnipers; ++i)
        {
            std::cin >> sniperOnPoint;
            ++snipersOnPoint[sniperOnPoint - 1];
        }

        for (const auto& edge: edges)
        {
            graph[edge.first - 1].emplace_back(std::make_pair(edge.second - 1, snipersOnPoint[edge.second - 1]));
        }

        std::cin >> origin >> destination;

        std::vector<int> optimalPath = dijkstra(graph, origin, destination);

        for (const auto& element : optimalPath)
        {
            std::cout << element << " ";
        }

    }

    return 0;
}