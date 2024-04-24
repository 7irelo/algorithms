class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.adj = [[] for _ in range(vertices)]
        self.time = 0

    def add_edge(self, u, v):
        self.adj[u].append(v)
        self.adj[v].append(u)

    def articulation_points(self):
        visited = [False] * self.V
        disc = [-1] * self.V
        low = [-1] * self.V
        parent = [-1] * self.V
        ap = set()

        def dfs(u):
            children = 0
            visited[u] = True
            disc[u] = self.time
            low[u] = self.time
            self.time += 1

            for v in self.adj[u]:
                if not visited[v]:
                    children += 1
                    parent[v] = u
                    dfs(v)
                    low[u] = min(low[u], low[v])

                    if parent[u] == -1 and children > 1:
                        ap.add(u)

                    if parent[u] != -1 and low[v] >= disc[u]:
                        ap.add(u)

                elif v != parent[u]:
                    low[u] = min(low[u], disc[v])

        for i in range(self.V):
            if not visited[i]:
                dfs(i)

        return ap

# Example usage
g = Graph(5)
g.add_edge(1, 0)
g.add_edge(0, 2)
g.add_edge(2, 1)
g.add_edge(0, 3)
g.add_edge(3, 4)

print("Articulation Points:", g.articulation_points())
