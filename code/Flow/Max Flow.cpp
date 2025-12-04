struct MaxFlow
{
    struct Edge
    {
        int v, rev, cap;
    };
    int n;
    vector<vector<Edge>> adj;

    MaxFlow(int n) : n(n)
    {
        adj.resize(n + 1);
    }
    void add_edge(int u, int v)
    {
        adj[u].push_back({v, (int)adj[v].size(), 1});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0});
    }
    bool bfs(int s, int t, vector<int> &parent, vector<int> &edge_index)
    {
        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < adj[u].size(); i++)
            {
                Edge &e = adj[u][i];
                if (!visited[e.v] && e.cap > 0)
                {
                    visited[e.v] = true;
                    parent[e.v] = u;
                    edge_index[e.v] = i;
                    if (e.v == t)
                        return true;
                    q.push(e.v);
                }
            }
        }
        return false;
    }
    int max_flow(int s, int t)
    {
        int total_flow = 0;
        while (true)
        {
            vector<int> parent(n + 1, -1), edge_index(n + 1, -1);
            if (!bfs(s, t, parent, edge_index))
                break;
            int push_flow = INT_MAX, cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                Edge &e = adj[prev][edge_index[cur]];
                push_flow = min(push_flow, e.cap);
                cur = prev;
            }
            cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                Edge &e = adj[prev][edge_index[cur]];
                e.cap -= push_flow;
                adj[cur][e.rev].cap += push_flow;
                cur = prev;
            }
            total_flow += push_flow;
        }
        return total_flow;
    }
    void dfs(int u, vector<bool> &visited)
    {
        visited[u] = true;
        for (const auto &e : adj[u])
        {
            if (e.cap > 0 && !visited[e.v])
            {
                dfs(e.v, visited);
            }
        }
    }
    vector<pair<int, int>> find_min_cut(int s)
    {
        vector<bool> visited(n + 1, false);
        dfs(s, visited);
        vector<pair<int, int>> cut_edges;
        for (int u = 1; u <= n; u++)
        {
            if (visited[u])
            {
                for (const auto &e : adj[u])
                {
                    if (!visited[e.v] && e.cap == 0)
                    {
                        cut_edges.emplace_back(u, e.v);
                    }
                }
            }
        }
        return cut_edges;
    }
};