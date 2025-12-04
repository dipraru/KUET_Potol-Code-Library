struct MinCostMaxFlow
{
    struct Edge
    {
        int v, rev;    // Destination and index of the reverse edge
        int cap, cost; // Capacity and cost of the edge
    };

    vector<vector<Edge>> adj;
    int n;

    MinCostMaxFlow(int n) : n(n)
    {
        adj.resize(n + 1); // 1-based indexing
    }

    void add_edge(int u, int v, int cap, int cost)
    {
        adj[u].push_back({v, (int)adj[v].size(), cap, cost});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0, -cost});
    }

    bool spfa(int s, int t, vector<int> &parent, vector<int> &edge_index, vector<int> &dist)
    {
        dist.assign(n + 1, INF);
        parent.assign(n + 1, -1);
        edge_index.assign(n + 1, -1);
        vector<bool> in_queue(n + 1, false);
        queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            in_queue[u] = false;
            for (int i = 0; i < adj[u].size(); i++)
            {
                Edge &e = adj[u][i];
                if (e.cap > 0 && dist[u] + e.cost < dist[e.v])
                {
                    dist[e.v] = dist[u] + e.cost;
                    parent[e.v] = u;
                    edge_index[e.v] = i;
                    if (!in_queue[e.v])
                    {
                        q.push(e.v);
                        in_queue[e.v] = true;
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    pair<int, int> max_flow(int s, int t)
    {
        int total_flow = 0, total_cost = 0;
        vector<int> parent, edge_index, dist;

        while (spfa(s, t, parent, edge_index, dist))
        {
            // Find the bottleneck capacity along the path
            int push_flow = INF, cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                Edge &e = adj[prev][edge_index[cur]];
                push_flow = min(push_flow, e.cap);
                cur = prev;
            }
            // Update the residual graph along the path
            cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                Edge &e = adj[prev][edge_index[cur]];
                e.cap -= push_flow;
                adj[e.v][e.rev].cap += push_flow;
                cur = prev;
            }
            total_flow += push_flow;
            total_cost += push_flow * dist[t];
        }

        return {total_flow, total_cost};
    }
};