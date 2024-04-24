class DisjointSet {
    constructor(size) {
        this.parent = Array.from({ length: size }, (_, i) => i);
        this.rank = Array(size).fill(0);
    }

    find(x) {
        if (this.parent[x] !== x) {
            this.parent[x] = this.find(this.parent[x]);
        }
        return this.parent[x];
    }

    union(x, y) {
        const rootX = this.find(x);
        const rootY = this.find(y);
        if (rootX !== rootY) {
            if (this.rank[rootX] < this.rank[rootY]) {
                this.parent[rootX] = rootY;
            } else if (this.rank[rootX] > this.rank[rootY]) {
                this.parent[rootY] = rootX;
            } else {
                this.parent[rootY] = rootX;
                this.rank[rootX]++;
            }
        }
    }
}

class Edge {
    constructor(source, destination, weight) {
        this.source = source;
        this.destination = destination;
        this.weight = weight;
    }
}

function kruskalMST(graph) {
    const sortedEdges = graph.sort((a, b) => a.weight - b.weight);
    const numVertices = graph.reduce((max, edge) => Math.max(max, edge.source, edge.destination), 0) + 1;
    const disjointSet = new DisjointSet(numVertices);
    const mst = [];

    for (let edge of sortedEdges) {
        const rootSource = disjointSet.find(edge.source);
        const rootDest = disjointSet.find(edge.destination);
        if (rootSource !== rootDest) {
            mst.push(edge);
            disjointSet.union(rootSource, rootDest);
        }
    }

    return mst;
}

// Example usage
const graph = [
    new Edge(0, 1, 4),
    new Edge(0, 2, 4),
    new Edge(1, 2, 2),
    new Edge(1, 0, 4),
    new Edge(2, 0, 4),
    new Edge(2, 1, 2),
    new Edge(2, 3, 3),
    new Edge(2, 5, 2),
    new Edge(2, 4, 4),
    new Edge(3, 2, 3),
    new Edge(4, 2, 4),
    new Edge(5, 2, 2)
];

const minimumSpanningTree = kruskalMST(graph);
console.log('Minimum Spanning Tree:', minimumSpanningTree);
