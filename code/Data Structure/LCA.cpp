#include <bits/stdc++.h>
using namespace std;

class LCA_BinaryLifting
{
public:
    int n, max_log;
    vector<vector<int>> adj;
    vector<vector<int>> ancestor;
    vector<int> depth;

    LCA_BinaryLifting(int n) : n(n)
    {
        adj.resize(n + 1);
        max_log = log2(n) + 1;
        ancestor.assign(n + 1, vector<int>(max_log, -1));
        depth.resize(n + 1);
    }
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int node, int parent)
    {
        ancestor[node][0] = parent;
        for (int i = 1; i < max_log; i++)
        {
            if (ancestor[node][i - 1] != -1)
            {
                ancestor[node][i] = ancestor[ancestor[node][i - 1]][i - 1];
            }
        }
        for (int neighbor : adj[node])
        {
            if (neighbor != parent)
            {
                depth[neighbor] = depth[node] + 1;
                dfs(neighbor, node);
            }
        }
    }
    void preprocess(int root)
    {
        depth[root] = 0;
        dfs(root, -1);
    }
    int get_lca(int u, int v)
    {
        if (depth[u] < depth[v])
        {
            swap(u, v);
        }
        for (int i = max_log - 1; i >= 0; i--)if (ancestor[u][i] != -1 && depth[ancestor[u][i]] >= depth[v]) u = ancestor[u][i];
        if (u == v)return u;
        for (int i = max_log - 1; i >= 0; i--)if (ancestor[u][i] != ancestor[v][i]) u = ancestor[u][i],v = ancestor[v][i];
        return ancestor[u][0];
    }
    int get_kth_ancestor(int u, int k)
    {
        for (int i = 0; i < max_log; i++)
        {
            if (k & (1 << i))
            {
                u = ancestor[u][i];
                if (u == -1) break;
            }
        }
        return u;
    }
    int query_distance(int u, int v)
    {
        int lca = get_lca(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }
    int get_kth_node_in_path(int u, int v, int k)
    {
        int lca = get_lca(u, v);
        int dist_u_lca = depth[u] - depth[lca];
        int dist_lca_v = depth[v] - depth[lca];
        int total_distance = dist_u_lca + dist_lca_v;
        if (k > total_distance) return -1;
        if (k <= dist_u_lca)return get_kth_ancestor(u, k);
        else return get_kth_ancestor(v, dist_u_lca + dist_lca_v - k);
    }
    int get_ancestor_depth(int u, int target_depth)
    {
        if (depth[u] < target_depth) return -1;
        int diff = depth[u] - target_depth;
        return get_kth_ancestor(u, diff);
    }
};
