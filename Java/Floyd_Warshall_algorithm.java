import java.util.Arrays;

public class FloydWarshallAlgorithm {
    static final int INF = Integer.MAX_VALUE; // Infinity represents absence of edge between vertices

    // Function to find all-pairs shortest paths using Floyd-Warshall algorithm
    public static void floydWarshall(int[][] graph) {
        int V = graph.length;

        // Create a 2D array dist[][] to store shortest distances between every pair of vertices
        int[][] dist = new int[V][V];

        // Initialize dist[][] with the values of the input graph
        for (int i = 0; i < V; i++)
            System.arraycopy(graph[i], 0, dist[i], 0, V);

        // Iterate through all vertices and calculate shortest paths
        for (int k = 0; k < V; k++) {
            // Pick all vertices as source one by one
            for (int i = 0; i < V; i++) {
                // Pick all vertices as destination for the above picked source
                for (int j = 0; j < V; j++) {
                    // If vertex k is on the shortest path from i to j,
                    // then update the value of dist[i][j]
                    if (dist[i][k] != INF && dist[k][j] != INF &&
                            dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Print the shortest distances
        printSolution(dist);
    }

    // Function to print the solution (shortest distances)
    public static void printSolution(int[][] dist) {
        int V = dist.length;
        System.out.println("Shortest distances between every pair of vertices:");
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INF)
                    System.out.print("INF ");
                else
                    System.out.print(dist[i][j] + "  ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        // Example graph represented as an adjacency matrix
        int[][] graph = {
                {0, 5, INF, 10},
                {INF, 0, 3, INF},
                {INF, INF, 0, 1},
                {INF, INF, INF, 0}
        };

        // Find all-pairs shortest paths
        floydWarshall(graph);
    }
}
