using System;
using System.Collections.Generic;
using System.Linq;

class KMeansClustering
{
    class Point
    {
        public double X { get; set; }
        public double Y { get; set; }

        public Point(double x, double y)
        {
            X = x;
            Y = y;
        }

        public double DistanceTo(Point other)
        {
            double dx = X - other.X;
            double dy = Y - other.Y;
            return Math.Sqrt(dx * dx + dy * dy);
        }
    }

    class Cluster
    {
        public Point Centroid { get; set; }
        public List<Point> Points { get; set; }

        public Cluster(Point centroid)
        {
            Centroid = centroid;
            Points = new List<Point>();
        }

        public void UpdateCentroid()
        {
            double sumX = Points.Sum(p => p.X);
            double sumY = Points.Sum(p => p.Y);
            Centroid = new Point(sumX / Points.Count, sumY / Points.Count);
        }

        public void ClearPoints()
        {
            Points.Clear();
        }
    }

    public static List<Cluster> KMeans(List<Point> points, int k, int maxIterations)
    {
        // Initialize clusters with random centroids
        Random random = new Random();
        List<Cluster> clusters = new List<Cluster>();
        for (int i = 0; i < k; i++)
        {
            Point randomPoint = points[random.Next(points.Count)];
            clusters.Add(new Cluster(randomPoint));
        }

        // Run iterations
        for (int iter = 0; iter < maxIterations; iter++)
        {
            // Assign points to clusters
            foreach (Point point in points)
            {
                Cluster closestCluster = null;
                double minDistance = double.MaxValue;
                foreach (Cluster cluster in clusters)
                {
                    double distance = point.DistanceTo(cluster.Centroid);
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestCluster = cluster;
                    }
                }
                closestCluster.Points.Add(point);
            }

            // Update centroids
            foreach (Cluster cluster in clusters)
            {
                cluster.UpdateCentroid();
            }
        }

        return clusters;
    }

    static void Main(string[] args)
    {
        // Generate sample data
        List<Point> points = new List<Point>();
        Random random = new Random();
        for (int i = 0; i < 100; i++)
        {
            double x = random.NextDouble() * 100;
            double y = random.NextDouble() * 100;
            points.Add(new Point(x, y));
        }

        // Run K-means clustering
        int k = 3; // Number of clusters
        int maxIterations = 100;
        List<Cluster> clusters = KMeans(points, k, maxIterations);

        // Output cluster centroids
        Console.WriteLine("Cluster centroids:");
        foreach (Cluster cluster in clusters)
        {
            Console.WriteLine($"Centroid: ({cluster.Centroid.X}, {cluster.Centroid.Y})");
        }
    }
}
