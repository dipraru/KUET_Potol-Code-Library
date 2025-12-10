//  O(V*E^2)
struct EdmondsKarp
{
    vector<vector<int>> capacity, adj;
    int n;

    EdmondsKarp(int n) : n(n)
    {
        capacity.assign(n + 1, vector<int>(n + 1, 0));
        adj.resize(n + 1);
    }
    void add_edge(int u, int v, int cap)
    {
        capacity[u][v] += cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // Reverse edge
    }
    int bfs(int s, int t, vector<int> &parent)
    {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INF});

        while (!q.empty())
        {
            auto [u, flow] = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (parent[v] == -1 && capacity[u][v] > 0)
                {
                    parent[v] = u;
                    int new_flow = min(flow, capacity[u][v]);
                    if (v == t) return new_flow;
                    q.push({v, new_flow});
                }
            }
        }
        return 0;
    }
    int max_flow(int s, int t)
    {
        int flow = 0, new_flow;
        vector<int> parent(n + 1);
        while ((new_flow = bfs(s, t, parent)) > 0)
        {
            flow += new_flow;
            int cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return flow;
    }
};