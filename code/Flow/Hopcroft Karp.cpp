//O(E*root(V))
class HopcroftKarp
{
public:
    int n, m;
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;
    HopcroftKarp(int n, int m) : n(n), m(m)
    {
        adj.resize(n + 1);
        pairU.assign(n + 1, 0);
        pairV.assign(m + 1, 0);
        dist.assign(n + 1, 0);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }
    bool bfs()
    {
        queue<int> q;
        for (int u = 1; u <= n; ++u)
        {
            if (pairU[u] == 0)
            {
                dist[u] = 0;
                q.push(u);
            }
            else dist[u] = INT_MAX;
        }
        dist[0] = INT_MAX;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (dist[u] < dist[0])
            {
                for (int v : adj[u])
                {
                    if (dist[pairV[v]] == INT_MAX)
                    {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return dist[0] != INT_MAX;
    }
    bool dfs(int u)
    {
        if (u == 0) return true;
        for (int v : adj[u])
        {
            if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))
            {
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }

    int maxMatching()
    {
        int matching = 0;
        while (bfs())
        {
            for (int u = 1; u <= n; ++u)
                if (pairU[u] == 0 && dfs(u)) matching++;
        }
        return matching;
    }
};

