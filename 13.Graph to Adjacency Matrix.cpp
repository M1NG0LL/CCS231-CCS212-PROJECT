#include <iostream>
#include <vector>
using namespace std;

void graph(int vert, const vector<pair<int, int>> &edges)

{
    vector<vector<int>> adjmat(vert, vector<int>(vert, 0)); // make a matrix with all zeros

    for (const auto &edge : edges)
    {
        int h = edge.first;
        int v = edge.second;
        // set the edges to 1
        adjmat[h][v] = 1;
        adjmat[v][h] = 1;
    }
    for (const auto &row : adjmat)
    {
        for (int value : row)
        {
            cout << value << " ";
        }

        cout << endl;
    }
}

int main()
{
    int vertices = 7;
    vector<pair<int, int>> edgez = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 4}, {1, 5}, {1, 6}, {4, 5}};
    graph(vertices, edgez);
    return 0;
}