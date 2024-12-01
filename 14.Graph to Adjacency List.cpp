#include <iostream>
#include <vector>
using namespace std;

void Graph_to_list(vector<vector<int>> graph) // O(N²)
{
    int graph_size = graph.size();

    for (int i = 0; i < graph_size; ++i)
    {
        cout << "Node " << i << ": ";
        int edge_size = graph[i].size();
        for (int j = 0; j < edge_size; ++j)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

int main() // O(N²)
{
    int nodes = 6;

    vector<vector<int>> graph(nodes);

    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0, 5};
    graph[3] = {1};
    graph[4] = {1};
    graph[5] = {2};

    Graph_to_list(graph);
}

// So the time Complexity of main is O(N²)