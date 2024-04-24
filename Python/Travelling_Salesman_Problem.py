import sys

def tsp(graph):
    n = len(graph)
    dp = [[None] * (1 << n) for _ in range(n)]

    # Base case: If there is only one city, return the distance from the city to itself
    for i in range(n):
        dp[i][1 << i] = graph[i][0]

    # Define a recursive function to find the shortest path
    def find_shortest_path(curr, visited):
        if dp[curr][visited] is not None:
            return dp[curr][visited]
        
        min_distance = sys.maxsize
        for next_city in range(n):
            if visited & (1 << next_city) == 0:
                distance = graph[curr][next_city] + find_shortest_path(next_city, visited | (1 << next_city))
                min_distance = min(min_distance, distance)
        
        dp[curr][visited] = min_distance
        return min_distance

    return find_shortest_path(0, 1)

# Example usage
graph = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
]
print("Shortest possible route length:", tsp(graph))
