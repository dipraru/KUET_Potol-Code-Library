struct DSU
{
    vector<int> parent, size;
    vector<pair<int, int>> history;
    int componentCount;
    DSU(int n) : parent(n + 1), size(n + 1, 1), componentCount(n){iota(parent.begin(), parent.end(), 0);}
    int find(int v)
    {
        if (parent[v] != v)return find(parent[v]);
        return parent[v];
    }
    bool merge(int u, int v)
    {
        u = find(u),v = find(v);
        if (u == v){return false;}
        if (size[u] < size[v])swap(u, v);
        history.push_back({v, size[v]});
        history.push_back({u, size[u]});
        parent[v] = u,size[u] += size[v],--componentCount;
        return true;
    }
    void rollback()
    {
        auto [u, oldSizeU] = history.back();
        history.pop_back();
        auto [v, oldSizeV] = history.back();
        history.pop_back();
        parent[v] = v,size[u] = oldSizeU,size[v] = oldSizeV,componentCount++;
    }
    int getComponentCount(){return componentCount;}
    bool same(int u, int v){return find(u) == find(v);}
    int getSize(int v){return size[find(v)];}
};
