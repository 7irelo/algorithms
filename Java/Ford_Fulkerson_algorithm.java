import java.util.*;

class FordFulkerson {
    static final int V = 6; // Number of vertices in the graph

    // Returns the maximum flow from source 's' to sink 't' in the given graph
    public int fordFulkerson(int graph[][], int s, int t) {
        int u, v;

        // Create a residual graph and fill the residual graph with given capacities in the original graph
        // Residual graph where rGraph[i][j] indicates residual capacity of edge from i to j (if there is an edge)
        int rGraph[][] = new int[V][V];

        for (u = 0; u < V; u++)
            for (v = 0; v < V; v++)
                rGraph[u][v] = graph[u][v];

        // Array to store path from source to sink
        int parent[] = new int[V];

        int maxFlow = 0; // Initialize max flow

        // Augment the flow while a path exists from source to sink
        while (bfs(rGraph, s, t, parent)) {
            int pathFlow = Integer.MAX_VALUE;

            // Find minimum residual capacity of the edges along the path filled by BFS.
            // Or find the maximum flow through the path found.
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                pathFlow = Math.min(pathFlow, rGraph[u][v]);
            }

            // Update residual capacities of the edges and reverse edges along the path
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
            }

            // Add path flow to overall flow
            maxFlow += pathFlow;
        }

        return maxFlow;
    }

    // Breadth-First Search (BFS) for finding augmenting paths
    boolean bfs(int rGraph[][], int s, int t, int parent[]) {
        boolean visited[] = new boolean[V];
        Queue<Integer> queue = new LinkedList<>();
        queue.add(s);
        visited[s] = true;
        parent[s] = -1;

        while (!queue.isEmpty()) {
            int u = queue.poll();

            for (int v = 0; v < V; v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    queue.add(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return visited[t]; // Return true if there is a path from source to sink in the residual graph
    }
}

public class Main {
    public static void main(String[] args) {
        // Example graph represented as an adjacency matrix
        int graph[][] = new int[][] {
                {0, 16, 13, 0, 0, 0},
                {0, 0, 10, 12, 0, 0},
                {0, 4, 0, 0, 14, 0},
                {0, 0, 9, 0, 0, 20},
                {0, 0, 0, 7, 0, 4},
                {0, 0, 0, 0, 0, 0}
        };

        FordFulkerson m = new FordFulkerson();

        int source = 0; // Source vertex
        int sink = 5;   // Sink (or target) vertex

        System.out.println("The maximum possible flow is " + m.fordFulkerson(graph, source, sink));
    }
}
