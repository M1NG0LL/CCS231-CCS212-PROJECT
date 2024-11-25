#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(const vector<vector<int>>& adjmat, int start, vector<bool>& visited) {
    int v = adjmat.size();
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS traversal starting from vertex " << start << ": ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        for (int i = 0; i < v; i++) {
            if (adjmat[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

int main() {
    int v = 7, x;
    vector<vector<int>> adjmat(v, vector<int>(v, 0));

    // Add edges
    adjmat[0][1] = adjmat[1][0] = 1;
    adjmat[1][2] = adjmat[2][1] = 1;
    adjmat[2][0] = adjmat[0][2] = 1;
    adjmat[3][0] = adjmat[0][3] = 1;
    adjmat[1][4] = adjmat[4][1] = 1;
    adjmat[4][5] = adjmat[5][4] = 1;
    adjmat[6][1] = adjmat[1][6] = 1;

    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            cout << adjmat[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Enter the number you want to start from within [0 to " << v - 1 << "]: ";
    cin >> x;

    if (x < 0 || x >= v) {
        cout << "Invalid vertex. Please enter a value between 0 and " << v - 1 << ".\n";
        return 1;
    }

    vector<bool> visited(v, false);
    bfs(adjmat, x, visited);


    return 0;
}
