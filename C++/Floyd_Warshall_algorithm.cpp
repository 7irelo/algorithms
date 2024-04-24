#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9; // Define infinity as a very large value

void floydWarshall(vector<vector<int>>& graph) {
    int V = graph.size();

    // Initialize distances matrix
    vector<vector<int>> dist(V, vector<int>(V, INF));

    // Initialize distances for direct edges
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                dist[i][j] = 0; // Distance to itself is 0
            } else if (graph[i][j] != INF) {
                dist[i][j] = graph[i][j];
            }
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Output the shortest distances
    cout << "Shortest distances between all pairs of vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

int main() {
    // Example graph represented by adjacency matrix
    vector<vector<int>> graph = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    // Run Floyd-Warshall algorithm
    floydWarshall(graph);

    return 0;
}
