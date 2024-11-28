#include <iostream>
#include <vector>
using namespace std;

void coloring(vector<vector<int>>& graph, int v) {
    vector<int> result(v, -1); // Initialize all vertices as uncolored (-1)
    vector<bool> available(v, false); // To check the availability of colors

    result[0] = 0; // Assign the first color to the first vertex

    // Assign colors to remaining vertices
    for (int i = 1; i < v; i++) {
        // Mark colors of adjacent vertices as unavailable
        for (int j : graph[i]) {
            if (result[j] != -1) {
                available[result[j]] = true;
            }
        }

        // Find the first available color
        int color;
        for (color = 0; color < v; color++) {
            if (!available[color]) {
                break;
            }
        }

        // Assign the found color to the current vertex
        result[i] = color;

        // Reset the availability for the next vertex
        for (int j : graph[i]) {
            if (result[j] != -1) {
                available[result[j]] = false;
            }
        }
    }

    // Print the result
    cout << "Vertex Colors:\n";
    for (int u = 0; u < v; u++) {
        cout << "Vertex " << u << " ---> Color " << result[u] << endl;
    }
}

int main() {
    int V = 6; // Number of vertices
    vector<vector<int>> graph(V);

    // Adjacency list representation of the graph
    graph[0] = {1, 2};
    graph[1] = {0, 2};
    graph[2] = {0, 1, 3, 4};
    graph[3] = {2, 4};
    graph[4] = {2, 3, 5};
    graph[5] = {4};

    coloring(graph, V);
    return 0;
}
