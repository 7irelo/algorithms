import java.util.*;

class Graph {
    class Edge implements Comparable<Edge> {
        int source, destination, weight;

        public Edge(int source, int destination, int weight) {
            this.source = source;
            this.destination = destination;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge compareEdge) {
            return this.weight - compareEdge.weight;
        }
    }

    private int V; // Number of vertices
    private List<Edge> edges; // List of edges in the graph

    public Graph(int V) {
        this.V = V;
        edges = new ArrayList<>();
    }

    // Function to add an edge to the graph
    public void addEdge(int source, int destination, int weight) {
        edges.add(new Edge(source, destination, weight));
    }

    // Function to find the MST using Kruskal's algorithm
    public void kruskalMST() {
        // Sort the edges by weight
        Collections.sort(edges);

        int[] parent = new int[V];
        for (int i = 0; i < V; i++) {
            parent[i] = i; // Initialize each vertex as its own parent
        }

        List<Edge> mst = new ArrayList<>();
        int mstWeight = 0;

        for (Edge edge : edges) {
            int rootSource = find(parent, edge.source);
            int rootDest = find(parent, edge.destination);

            // If including this edge does not cause a cycle, add it to the MST
            if (rootSource != rootDest) {
                mst.add(edge);
                mstWeight += edge.weight;
                union(parent, rootSource, rootDest);
            }
        }

        // Print the MST and its weight
        System.out.println("Minimum Spanning Tree:");
        for (Edge edge : mst) {
            System.out.println(edge.source + " - " + edge.destination + " : " + edge.weight);
        }
        System.out.println("Total Weight: " + mstWeight);
    }

    // Function to find the root of a vertex using path compression
    private int find(int[] parent, int vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent, parent[vertex]);
        }
        return parent[vertex];
    }

    // Function to perform union of two sets using union by rank
    private void union(int[] parent, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        parent[rootX] = rootY;
    }
}

public class Main {
    public static void main(String[] args) {
        int V = 6; // Number of vertices
        Graph graph = new Graph(V);

        // Add edges to the graph
        graph.addEdge(0, 1, 4);
        graph.addEdge(0, 2, 4);
        graph.addEdge(1, 2, 2);
        graph.addEdge(1, 0, 4);
        graph.addEdge(2, 0, 4);
        graph.addEdge(2, 1, 2);
        graph.addEdge(2, 3, 3);
        graph.addEdge(2, 5, 2);
        graph.addEdge(2, 4, 4);
        graph.addEdge(3, 2, 3);
        graph.addEdge(4, 2, 4);
        graph.addEdge(5, 2, 2);

        // Find the MST using Kruskal's algorithm
        graph.kruskalMST();
    }
}
