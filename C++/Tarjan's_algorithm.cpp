#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices

    // Adjacency list representation of graph
    vector<vector<int>> adj;

    // Helper function for Tarjan's algorithm
    void tarjanSCC(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& stackMember, vector<vector<int>>& SCCs, int& time) {
        disc[u] = low[u] = ++time;
        st.push(u);
        stackMember[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) { // If v is not visited yet
                tarjanSCC(v, disc, low, st, stackMember, SCCs, time);
                low[u] = min(low[u], low[v]);
            } else if (stackMember[v]) { // If v is in the stack
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is the root of an SCC
        if (low[u] == disc[u]) {
            vector<int> currSCC;
            while (true) {
                int v = st.top();
                st.pop();
                stackMember[v] = false;
                currSCC.push_back(v);
                if (v == u)
                    break;
            }
            SCCs.push_back(currSCC);
        }
    }

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Function to find strongly connected components using Tarjan's algorithm
    vector<vector<int>> findSCCs() {
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<bool> stackMember(V, false);
        stack<int> st;
        vector<vector<int>> SCCs;
        int time = 0;

        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                tarjanSCC(i, disc, low, st, stackMember, SCCs, time);
            }
        }

        return SCCs;
    }
};

int main() {
    // Create a graph given in the example
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    // Find strongly connected components
    vector<vector<int>> SCCs = g.findSCCs();

    // Output SCCs
    cout << "Strongly Connected Components:\n";
    for (const auto& SCC : SCCs) {
        for (int v : SCC) {
            cout << v << " ";
        }
        cout << "\n";
    }

    return 0;
}