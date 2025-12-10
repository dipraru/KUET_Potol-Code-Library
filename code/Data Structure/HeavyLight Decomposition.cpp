struct HLD{
    vector<vector<int>> adj;
    vector<int> par, dep, heavy, head, pos, sub;
    SegTree segTree;
    int curPos;
    HLD(int n) : adj(n + 1),par(n + 1, -1),dep(n + 1, 0),heavy(n + 1, -1),head(n + 1),pos(n + 1), sub(n + 1, 0),segTree(n),curPos(1) {}
    int dfs(int u)
    {
        sub[u] = 1;
        int mxsub = 0;
        for (int v : adj[u])
        {
            if (v == par[u])
                continue;
            par[v] = u;
            dep[v] = dep[u] + 1;
            int subtree = dfs(v);
            sub[u] += subtree;
            if (subtree > mxsub)
            {
                mxsub = subtree;
                heavy[u] = v;
            }
        }
        return sub[u];
    }
    void decompose(int u, int h)
    {
        head[u] = h;
        pos[u] = curPos++;
        if (heavy[u] != -1)
            decompose(heavy[u], h);
        for (int v : adj[u])
        {
            if (v != par[u] && v != heavy[u])
                decompose(v, v);
        }
    }
    void init(int root = 1)
    {
        dfs(root);
        decompose(root, root);
    }
    void updatePath(int u, int v, ll value, bool isEdge = false)
    {
        while (head[u] != head[v])
        {
            if (dep[head[u]] < dep[head[v]])
                swap(u, v);
            segTree.update(pos[head[u]], pos[u], value);
            u = par[head[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        segTree.update(pos[u] + isEdge, pos[v], value);
    }
    ll queryPath(int u, int v, bool isEdge = false)
    {
        ll result = 0;
        while (head[u] != head[v])
        {
            if (dep[head[u]] < dep[head[v]])
                swap(u, v);
            result = max(result, segTree.query(pos[head[u]], pos[u]));
            u = par[head[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        result = max(result, segTree.query(pos[u] + isEdge, pos[v]));
        return result;
    }
};