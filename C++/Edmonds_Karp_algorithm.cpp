#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Define infinity as a very large value
const int INF = INT_MAX;

// Structure to represent an edge in the graph
struct Edge {
    int v, flow, capacity;
};

class Graph {
    int V;
    vector<vector<Edge>> adj;

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, int capacity) {
        Edge forward = {v, 0, capacity};
        Edge backward = {u, 0, 0}; // Residual edge
        adj[u].push_back(forward);
        adj[v].push_back(backward);
    }

    // Breadth-first search to find augmenting paths
    bool bfs(int source, int sink, vector<int>& parent) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& edge : adj[u]) {
                int v = edge.v;
                if (!visited[v] && edge.capacity > edge.flow) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return visited[sink];
    }

    // Edmonds-Karp algorithm to find the maximum flow
    int maxFlow(int source, int sink) {
        int maxFlow = 0;
        vector<int> parent(V, -1);

        while (bfs(source, sink, parent)) {
            int pathFlow = INF;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (const Edge& edge : adj[u]) {
                    if (edge.v == v) {
                        pathFlow = min(pathFlow, edge.capacity - edge.flow);
                        break;
                    }
                }
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (Edge& edge : adj[u]) {
                    if (edge.v == v) {
                        edge.flow += pathFlow;
                        break;
                    }
                }
                for (Edge& edge : adj[v]) {
                    if (edge.v == u) {
                        edge.flow -= pathFlow;
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }
};

int main() {
    // Create a flow network given in the example
    Graph g(6);
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    int source = 0;
    int sink = 5;
    int maxFlow = g.maxFlow(source, sink);

    cout << "Maximum Flow from " << source << " to " << sink << " is: " << maxFlow << endl;

    return 0;
}
