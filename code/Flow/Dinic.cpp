// O(V^2*E)
struct Dinic
{
    vector<vector<int>> adj, capacity;
    vector<int> level, ptr;
    int n;

    Dinic(int n) : n(n)
    {
        adj.resize(n + 1);
        capacity.assign(n + 1, vector<int>(n + 1, 0));
        level.resize(n + 1);
        ptr.resize(n + 1);
    }

    void add_edge(int u, int v, int cap)
    {
        capacity[u][v] += cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (level[v] == -1 && capacity[u][v] > 0)
                {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int flow)
    {
        if (u == t || flow == 0)
            return flow;
        for (int &i = ptr[u]; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (level[v] == level[u] + 1 && capacity[u][v] > 0)
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
        int flow = 0;
        while (bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);
            while (int new_flow = dfs(s, t, INF))
            {
                flow += new_flow;
            }
        }
        return flow;
    }
};
