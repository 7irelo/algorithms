using System;
using System.Collections.Generic;

class AStarAlgorithm
{
    class Node
    {
        public int X { get; set; }
        public int Y { get; set; }
        public bool IsObstacle { get; set; }
        public List<Node> Neighbors { get; set; }
        public double G { get; set; } // Cost from start node to current node
        public double H { get; set; } // Heuristic cost from current node to goal node
        public double F => G + H; // Total estimated cost

        public Node Parent { get; set; }

        public Node(int x, int y, bool isObstacle = false)
        {
            X = x;
            Y = y;
            IsObstacle = isObstacle;
            Neighbors = new List<Node>();
            G = double.MaxValue;
            H = 0;
            Parent = null;
        }
    }

    // A* search algorithm
    public static List<Node> FindPath(Node start, Node goal)
    {
        HashSet<Node> openSet = new HashSet<Node>();
        HashSet<Node> closedSet = new HashSet<Node>();
        openSet.Add(start);

        while (openSet.Count > 0)
        {
            Node current = GetLowestFScoreNode(openSet);

            if (current == goal)
                return ReconstructPath(current);

            openSet.Remove(current);
            closedSet.Add(current);

            foreach (Node neighbor in current.Neighbors)
            {
                if (neighbor.IsObstacle || closedSet.Contains(neighbor))
                    continue;

                double tentativeGScore = current.G + CalculateDistance(current, neighbor);

                if (!openSet.Contains(neighbor))
                    openSet.Add(neighbor);
                else if (tentativeGScore >= neighbor.G)
                    continue;

                neighbor.Parent = current;
                neighbor.G = tentativeGScore;
                neighbor.H = CalculateDistance(neighbor, goal);
            }
        }

        return null; // No path found
    }

    // Helper method to calculate Euclidean distance between two nodes
    private static double CalculateDistance(Node a, Node b)
    {
        return Math.Sqrt(Math.Pow(a.X - b.X, 2) + Math.Pow(a.Y - b.Y, 2));
    }

    // Helper method to get the node with the lowest F score from the set
    private static Node GetLowestFScoreNode(HashSet<Node> set)
    {
        Node lowestNode = null;
        double lowestFScore = double.MaxValue;

        foreach (Node node in set)
        {
            if (node.F < lowestFScore)
            {
                lowestFScore = node.F;
                lowestNode = node;
            }
        }

        return lowestNode;
    }

    // Helper method to reconstruct the path from goal node to start node
    private static List<Node> ReconstructPath(Node goal)
    {
        List<Node> path = new List<Node>();
        Node current = goal;

        while (current != null)
        {
            path.Add(current);
            current = current.Parent;
        }

        path.Reverse();
        return path;
    }

    // Example usage
    static void Main(string[] args)
    {
        // Create a grid of nodes
        int gridSizeX = 5;
        int gridSizeY = 5;
        Node[,] grid = new Node[gridSizeX, gridSizeY];

        for (int x = 0; x < gridSizeX; x++)
        {
            for (int y = 0; y < gridSizeY; y++)
            {
                grid[x, y] = new Node(x, y);
            }
        }

        // Add neighbors to each node
        for (int x = 0; x < gridSizeX; x++)
        {
            for (int y = 0; y < gridSizeY; y++)
            {
                if (x > 0)
                    grid[x, y].Neighbors.Add(grid[x - 1, y]);
                if (x < gridSizeX - 1)
                    grid[x, y].Neighbors.Add(grid[x + 1, y]);
                if (y > 0)
                    grid[x, y].Neighbors.Add(grid[x, y - 1]);
                if (y < gridSizeY - 1)
                    grid[x, y].Neighbors.Add(grid[x, y + 1]);
            }
        }

        // Define obstacles
        grid[1, 2].IsObstacle = true;
        grid[2, 2].IsObstacle = true;
        grid[3, 2].IsObstacle = true;

        // Find path using A* algorithm
        Node startNode = grid[0, 0];
        Node goalNode = grid[4, 4];
        List<Node> path = FindPath(startNode, goalNode);

        // Output path
        if (path != null)
        {
            Console.WriteLine("Path found:");
            foreach (Node node in path)
            {
                Console.WriteLine($"({node.X}, {node.Y})");
            }
        }
        else
        {
            Console.WriteLine("No path found.");
        }
    }
}
