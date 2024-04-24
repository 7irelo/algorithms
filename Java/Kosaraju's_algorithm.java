import java.util.*;

class Graph {
    private int V; // Number of vertices
    private List<Integer>[] adjList; // Adjacency list representation of the graph

    public Graph(int V) {
        this.V = V;
        adjList = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adjList[i] = new ArrayList<>();
        }
    }

    // Function to add an edge to the graph
    public void addEdge(int u, int v) {
        adjList[u].add(v);
    }

    // Function to perform Depth First Search (DFS)
    private void dfs(int v, boolean[] visited, Stack<Integer> stack) {
        visited[v] = true;
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, stack);
            }
        }
        stack.push(v);
    }

    // Function to perform a Depth First Search (DFS) on the transpose of the graph
    private void dfsTranspose(int v, boolean[] visited, List<Integer> component) {
        visited[v] = true;
        component.add(v);
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsTranspose(neighbor, visited, component);
            }
        }
    }

    // Function to find all strongly connected components (SCCs) in the graph
    public List<List<Integer>> kosaraju() {
        Stack<Integer> stack = new Stack<>();
        boolean[] visited = new boolean[V];

        // Step 1: Perform DFS and fill the stack with vertices in their finishing order
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, visited, stack);
            }
        }

        // Transpose the graph (reverse all edges)
        Graph transposeGraph = getTranspose();

        // Step 2: Perform DFS on the transpose graph and find SCCs
        Arrays.fill(visited, false);
        List<List<Integer>> sccList = new ArrayList<>();
        while (!stack.isEmpty()) {
            int v = stack.pop();
            if (!visited[v]) {
                List<Integer> component = new ArrayList<>();
                transposeGraph.dfsTranspose(v, visited, component);
                sccList.add(component);
            }
        }

        return sccList;
    }

    // Function to get the transpose of the graph (reverse all edges)
    private Graph getTranspose() {
        Graph transposeGraph = new Graph(V);
        for (int v = 0; v < V; v++) {
            for (int neighbor : adjList[v]) {
                transposeGraph.addEdge(neighbor, v);
            }
        }
        return transposeGraph;
    }
}

public class Main {
    public static void main(String[] args) {
        int V = 5; // Number of vertices
        Graph graph = new Graph(V);

        // Add edges to the graph
        graph.addEdge(1, 0);
        graph.addEdge(0, 2);
        graph.addEdge(2, 1);
        graph.addEdge(0, 3);
        graph.addEdge(3, 4);

        // Find strongly connected components (SCCs) using Kosaraju's algorithm
        List<List<Integer>> sccList = graph.kosaraju();

        // Print SCCs
        System.out.println("Strongly Connected Components:");
        for (List<Integer> component : sccList) {
            System.out.println(component);
        }
    }
}
