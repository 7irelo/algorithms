import java.util.*;

class TarjanSCC {
    private int V; // Number of vertices
    private List<Integer>[] adjList; // Adjacency list representation of the graph
    private int[] disc; // Discovery time of vertices
    private int[] low; // Earliest visited vertex reachable from subtree rooted with current vertex
    private boolean[] onStack; // To check if a vertex is on the recursion stack
    private Stack<Integer> stack; // Stack to store vertices in current SCC
    private List<List<Integer>> sccList; // List to store all SCCs

    public TarjanSCC(int vertices) {
        this.V = vertices;
        this.adjList = new ArrayList[V];
        for (int i = 0; i < V; i++)
            adjList[i] = new ArrayList<>();
        this.disc = new int[V];
        this.low = new int[V];
        this.onStack = new boolean[V];
        this.stack = new Stack<>();
        this.sccList = new ArrayList<>();
    }

    // Function to add an edge to the graph
    public void addEdge(int u, int v) {
        adjList[u].add(v);
    }

    // Function to perform Tarjan's Algorithm to find SCCs
    public void tarjanSCC() {
        // Initialize discovery and low values
        Arrays.fill(disc, -1);
        Arrays.fill(low, -1);

        for (int i = 0; i < V; i++) {
            if (disc[i] == -1)
                tarjanDFS(i);
        }
    }

    // DFS traversal for Tarjan's Algorithm
    private void tarjanDFS(int u) {
        disc[u] = low[u] = stack.size();
        stack.push(u);
        onStack[u] = true;

        for (int v : adjList[u]) {
            if (disc[v] == -1) {
                tarjanDFS(v);
                low[u] = Math.min(low[u], low[v]);
            } else if (onStack[v]) {
                low[u] = Math.min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            List<Integer> component = new ArrayList<>();
            int w;
            do {
                w = stack.pop();
                onStack[w] = false;
                component.add(w);
            } while (w != u);
            sccList.add(component);
        }
    }

    // Function to print all SCCs
    public void printSCCs() {
        System.out.println("Strongly Connected Components:");
        for (List<Integer> component : sccList) {
            System.out.println(component);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        TarjanSCC g = new TarjanSCC(5);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 0);
        g.addEdge(3, 0);
        g.addEdge(3, 4);

        g.tarjanSCC();
        g.printSCCs();
    }
}
