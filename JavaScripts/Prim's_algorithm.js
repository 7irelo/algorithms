class Graph {
    constructor() {
        this.vertices = new Map(); // Map to store vertices and their adjacent vertices
    }

    addVertex(vertex) {
        if (!this.vertices.has(vertex)) {
            this.vertices.set(vertex, new Map());
        }
    }

    addEdge(vertex1, vertex2, weight) {
        this.addVertex(vertex1);
        this.addVertex(vertex2);

        this.vertices.get(vertex1).set(vertex2, weight);
        this.vertices.get(vertex2).set(vertex1, weight); // For undirected graph
    }

    primMST() {
        const mst = new Set(); // Set to store the vertices in the MST
        const startVertex = [...this.vertices.keys()][0]; // Start with an arbitrary vertex

        mst.add(startVertex); // Add start vertex to MST

        while (mst.size < this.vertices.size) {
            let minWeight = Infinity;
            let minEdge = null;

            // Find the minimum weight edge that connects the MST to a non-tree vertex
            for (let vertex of mst) {
                for (let [adjVertex, weight] of this.vertices.get(vertex)) {
                    if (!mst.has(adjVertex) && weight < minWeight) {
                        minWeight = weight;
                        minEdge = [vertex, adjVertex];
                    }
                }
            }

            const [vertex1, vertex2] = minEdge;
            mst.add(vertex2); // Add the new vertex to the MST
            console.log(`Added edge: ${vertex1} - ${vertex2}`);
        }
    }
}

// Example graph represented as an adjacency list
const graph = new Graph();
graph.addEdge('A', 'B', 2);
graph.addEdge('A', 'C', 3);
graph.addEdge('B', 'C', 1);
graph.addEdge('B', 'D', 1);
graph.addEdge('C', 'D', 1);

// Find the minimum spanning tree using Prim's algorithm
graph.primMST();
