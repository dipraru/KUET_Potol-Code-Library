// O(E*F),  where F is the maximum flow value.
struct FordFulkerson
{
    vector<vector<int>> capacity, adj;
    vector<bool> visited;
    int n;

    FordFulkerson(int n) : n(n)
    {
        capacity.assign(n + 1, vector<int>(n + 1, 0));
        adj.resize(n + 1);
    }

    void add_edge(int u, int v, int cap)
    {
        capacity[u][v] += cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // Reverse edge for residual graph
    }

    int dfs(int u, int t, int flow)
    {
        if (u == t)
            return flow;
        visited[u] = true;
        for (int v : adj[u])
        {
            if (!visited[v] && capacity[u][v] > 0)
            {
                int bottleneck = dfs(v, t, min(flow, capacity[u][v]));
                if (bottleneck > 0)
                {
                    capacity[u][v] -= bottleneck;
                    capacity[v][u] += bottleneck;
                    return bottleneck;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t)
    {
        int flow = 0, new_flow;
        do
        {
            visited.assign(n + 1, false);
            new_flow = dfs(s, t, INF);
            flow += new_flow;
        } while (new_flow > 0);
        return flow;
    }
};
