#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, vector<vector<int>> graph, vector<bool> visited)
{
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, graph, visited);
        }
    }
}

int main()
{
    int nodes = 6;

    vector<vector<int>> graph(nodes);

    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0, 5};
    graph[3] = {1};
    graph[4] = {1};
    graph[5] = {2};

    vector<bool> visited(nodes, false);

    cout << "DFS traversal starting from node 0: ";
    dfs(0, graph, visited);
}