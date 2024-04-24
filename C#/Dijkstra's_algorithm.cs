using System;
using System.Collections.Generic;

class DijkstraAlgorithm
{
    // Class to represent a graph node
    class Node
    {
        public int Id { get; set; }
        public Dictionary<Node, int> Neighbors { get; set; } // Key: Neighbor node, Value: Edge weight
        public int DistanceFromSource { get; set; } = int.MaxValue; // Distance from the source node
        public Node PreviousNode { get; set; } = null; // Previous node in the shortest path

        public Node(int id)
        {
            Id = id;
            Neighbors = new Dictionary<Node, int>();
        }
    }

    // Method to find the shortest path using Dijkstra's algorithm
    public static List<Node> FindShortestPath(Dictionary<int, Node> graph, Node source, Node destination)
    {
        source.DistanceFromSource = 0;
        var unvisited = new HashSet<Node>(graph.Values);

        while (unvisited.Count > 0)
        {
            var currentNode = GetClosestNode(unvisited);
            unvisited.Remove(currentNode);

            foreach (var neighbor in currentNode.Neighbors)
            {
                int tentativeDistance = currentNode.DistanceFromSource + neighbor.Value;
                if (tentativeDistance < neighbor.Key.DistanceFromSource)
                {
                    neighbor.Key.DistanceFromSource = tentativeDistance;
                    neighbor.Key.PreviousNode = currentNode;
                }
            }
        }

        return GetShortestPath(destination);
    }

    // Helper method to get the closest node from the unvisited set
    private static Node GetClosestNode(HashSet<Node> unvisited)
    {
        Node closestNode = null;
        int minDistance = int.MaxValue;

        foreach (var node in unvisited)
        {
            if (node.DistanceFromSource < minDistance)
            {
                minDistance = node.DistanceFromSource;
                closestNode = node;
            }
        }

        return closestNode;
    }

    // Helper method to get the shortest path from destination node back to the source node
    private static List<Node> GetShortestPath(Node destination)
    {
        var path = new List<Node>();
        Node currentNode = destination;

        while (currentNode != null)
        {
            path.Add(currentNode);
            currentNode = currentNode.PreviousNode;
        }

        path.Reverse();
        return path;
    }

    // Example usage
    static void Main(string[] args)
    {
        // Create graph
        var node1 = new Node(1);
        var node2 = new Node(2);
        var node3 = new Node(3);
        var node4 = new Node(4);

        node1.Neighbors.Add(node2, 5);
        node1.Neighbors.Add(node3, 10);
        node2.Neighbors.Add(node3, 3);
        node2.Neighbors.Add(node4, 2);
        node3.Neighbors.Add(node4, 1);

        var graph = new Dictionary<int, Node>
        {
            { node1.Id, node1 },
            { node2.Id, node2 },
            { node3.Id, node3 },
            { node4.Id, node4 }
        };

        // Find shortest path from node1 to node4
        var shortestPath = FindShortestPath(graph, node1, node4);

        // Output shortest path
        Console.WriteLine("Shortest path from node 1 to node 4:");
        foreach (var node in shortestPath)
        {
            Console.Write(node.Id + " ");
        }
        Console.WriteLine();
    }
}
