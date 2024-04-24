#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define infinity as a very large value
const int INF = numeric_limits<int>::max();

// Structure to represent a graph edge
struct Edge {
    int dest;
    int weight;
};

// Structure to represent a graph node
struct Node {
    int id;
    int distance;
};

// Comparison function for priority queue
struct CompareDistance {
    bool operator()(const Node& a, const Node& b) const {
        return a.distance > b.distance;
    }
};

// Dijkstra's algorithm to find the shortest path
vector<int> dijkstra(const vector<vector<Edge>>& graph, int source) {
    int numNodes = graph.size();
    vector<int> distance(numNodes, INF);
    vector<bool> visited(numNodes, false);
    
    // Priority queue to store nodes with their distances
    priority_queue<Node, vector<Node>, CompareDistance> pq;
    pq.push({source, 0});
    distance[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().id;
        pq.pop();

        // If the node is already visited, skip
        if (visited[u]) continue;
        visited[u] = true;

        // Update distances of adjacent nodes
        for (const Edge& edge : graph[u]) {
            int v = edge.dest;
            int weight = edge.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({v, distance[v]});
            }
        }
    }

    return distance;
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes and edges: ";
    cin >> numNodes >> numEdges;

    // Initialize the graph
    vector<vector<Edge>> graph(numNodes);
    cout << "Enter edges in the format 'source destination weight':" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int source, dest, weight;
        cin >> source >> dest >> weight;
        graph[source].push_back({dest, weight});
        // Uncomment the line below if the graph is undirected
        // graph[dest].push_back({source, weight});
    }

    int sourceNode;
    cout << "Enter the source node: ";
    cin >> sourceNode;

    // Run Dijkstra's algorithm
    vector<int> shortestDistances = dijkstra(graph, sourceNode);

    // Output shortest distances from source node to all other nodes
    cout << "Shortest distances from node " << sourceNode << ":" << endl;
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": ";
        if (shortestDistances[i] == INF)
            cout << "INF";
        else
            cout << shortestDistances[i];
        cout << endl;
    }

    return 0;
}