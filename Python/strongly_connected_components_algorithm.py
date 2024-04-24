class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.adj = [[] for _ in range(vertices)]
        self.time = 0

    def add_edge(self, u, v):
        self.adj[u].append(v)

    def tarjan_SCC(self):
        low = [float("Inf")] * self.V
        disc = [-1] * self.V
        stackMember = [False] * self.V
        st = []
        result = []

        def dfs(u):
            disc[u] = self.time
            low[u] = self.time
            self.time += 1
            st.append(u)
            stackMember[u] = True

            for v in self.adj[u]:
                if disc[v] == -1:
                    dfs(v)
                    low[u] = min(low[u], low[v])
                elif stackMember[v]:
                    low[u] = min(low[u], disc[v])

            w = -1
            if low[u] == disc[u]:
                component = []
                while w != u:
                    w = st.pop()
                    stackMember[w] = False
                    component.append(w)
                result.append(component)

        for i in range(self.V):
            if disc[i] == -1:
                dfs(i)

        return result


# Example usage
g = Graph(5)
g.add_edge(1, 0)
g.add_edge(0, 2)
g.add_edge(2, 1)
g.add_edge(0, 3)
g.add_edge(3, 4)

print("Strongly Connected Components:")
print(g.tarjan_SCC())
