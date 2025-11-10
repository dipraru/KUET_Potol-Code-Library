#include <bits/stdc++.h>
using namespace std;

struct Graph
{
    int N;
    bool directed;
    vector<vector<int>> adj;

    Graph(int n, bool dir = false) : N(n), directed(dir), adj(n + 1) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }
    vector<int> bfs(int src)
    {
        vector<bool> vis(N + 1, false), par(N + 1, -1);
        vector<int> order;
        queue<int> q;
        vis[src] = true;
        q.push(src);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u])
                if (vis[v]) continue;
                vis[v] = true,par[v] = u;
                q.push(v);
        }
        return order;
    }
    pair<int, int> farthestNode(int src)
    {
        vector<int> d = bfs(src);
        int md = -1;
        int node = src;
        for (int i = 1; i <= N; i++)
            if (d[i] > md) md = d[i],node = i;
        return {node, (int)md};
    }
    int diameter()
    {
        auto [u, _] = farthestNode(1);
        auto [v, dia] = farthestNode(u);
        return dia;
    }

    vector<int> dfs(int src)
    {
        vector<bool> vis(N + 1, false);
        vector<int> post;
        function<void(int)> dfsU = [&](int u)
        {
            vis[u] = true;
            for (int v : adj[u]) 
            if (!vis[v]) dfsU(v);
            post.push_back(u);
        };
        dfsU(src);
        return post;
    }
    bool isBipartite()
    {
        vector<int> color(N + 1, -1);
        for (int i = 1; i <= N; ++i)
        {
            if (color[i] != -1) continue
            queue<int> q;
            color[i] = 0;
            q.push(i);
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int v : adj[u])
                {
                    if (color[v] == -1)
                    {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    }
                    else if (color[v] == color[u])return false;
                }
            }
        }
        return true;
    }

    vector<vector<int>> getConnectedComponents()
    {
        vector<bool> vis(N + 1, false);
        vector<vector<int>> comps;
        for (int i = 1; i <= N; ++i)
        {
            if (!vis[i])
            {
                vector<int> comp;
                queue<int> q;
                vis[i] = true;
                q.push(i);
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    comp.push_back(u);
                    for (int v : adj[u])
                        if (!vis[v])
                        {
                            vis[v] = true;
                            q.push(v);
                        }
                }
                comps.push_back(comp);
            }
        }
        return comps;
    }
    vector<vector<int>> getCycleComponentsDirected()
    {
        vector<int> color(N + 1, 0);
        vector<int> parent(N + 1, -1);
        vector<vector<int>> cycles;
        vector<int> stack;

        function<void(int)> dfs = [&](int u)
        {
            color[u] = 1;
            stack.push_back(u);
            for (int v : adj[u])
            {
                if (color[v] == 0) parent[v] = u,dfs(v);
                else if (color[v] == 1)
                {
                    vector<int> cycle;
                    for (int i = stack.size() - 1; i >= 0; --i)
                    {
                        cycle.push_back(stack[i]);
                        if (stack[i] == v) break;
                    }
                    reverse(cycle.begin(), cycle.end());
                    cycles.push_back(cycle);
                }
            }
            stack.pop_back();
            color[u] = 2;
        };
        for (int i = 1; i <= N; ++i)
            if (color[i] == 0) dfs(i);
        return cycles;
    }

    bool hasCycleUndirected()
    {
        vector<bool> vis(N + 1, false);
        function<bool(int, int)> dfsU = [&](int u, int p)
        {
            vis[u] = true;
            for (int v : adj[u])
            {
                if (!vis[v]){
                    if (dfsU(v, u)) return true;
                }
                else if (v != p) return true;
            }
            return false;
        };
        for (int i = 1; i <= N; i++)
            if (!vis[i] && dfsU(i, -1))return true;
        return false;
    }
    vector<int> topoSortKahn()
    {
        vector<int> indeg(N + 1, 0);
        for (int u = 1; u <= N; u++)
            for (int v : adj[u])
                indeg[v]++;
        queue<int> q;
        for (int i = 1; i <= N; i++)
            if (indeg[i] == 0)
                q.push(i);
        vector<int> order;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u])
                if (--indeg[v] == 0)
                    q.push(v);
        }
        return ((int)order.size() == N ? order : vector<int>{});
    }

    vector<int> topoSortDFS()
    {
        vector<bool> vis(N + 1, false);
        stack<int> st;
        function<void(int)> dfsT = [&](int u)
        {
            vis[u] = true;
            for (int v : adj[u])
                if (!vis[v]) dfsT(v);
            st.push(u);
        };
        for (int i = 1; i <= N; i++)
            if (!vis[i]) dfsT(i);
        vector<int> order;
        while (!st.empty())
        {
            order.push_back(st.top());
            st.pop();
        }
        return order;
    }
    vector<int> idx, low, compID;
    vector<bool> inStack;
    stack<int> stk;
    int timeStamp = 0, sccCount = 0;

    void tarjanDFS(int u)
    {
        idx[u] = low[u] = ++timeStamp;
        stk.push(u);
        inStack[u] = true;
        for (int v : adj[u])
        {
            if (!idx[v])
            {
                tarjanDFS(v);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v])
                low[u] = min(low[u], idx[v]);
        }
        if (low[u] == idx[u])
        {
            sccCount++;
            while (true)
            {
                int w = stk.top();
                stk.pop();
                inStack[w] = false;
                compID[w] = sccCount;
                if (w == u) break;
            }
        }
    }

    vector<vector<int>> getSCCs()
    {
        idx.assign(N + 1, 0);
        low.assign(N + 1, 0);
        compID.assign(N + 1, 0);
        inStack.assign(N + 1, false);
        timeStamp = sccCount = 0;
        for (int i = 1; i <= N; i++)
            if (!idx[i]) tarjanDFS(i);
        vector<vector<int>> comps(sccCount + 1);
        for (int i = 1; i <= N; i++)
            comps[compID[i]].push_back(i);
        return comps;
    }
    vector<int> disc, lowB;
    vector<bool> visB, isArt;
    vector<pair<int, int>> bridges;
    int dfsTime = 0;

    void dfsBrAP(int u, int parent)
    {
        visB[u] = true;
        disc[u] = lowB[u] = ++dfsTime;
        int children = 0;
        for (int v : adj[u])
        {
            if (!visB[v])
            {
                children++;
                dfsBrAP(v, u);
                lowB[u] = min(lowB[u], lowB[v]);
                if (parent != -1 && lowB[v] >= disc[u]) isArt[u] = true;
                if (lowB[v] > disc[u]) bridges.emplace_back(u, v);
            }
            else if (v != parent) lowB[u] = min(lowB[u], disc[v]);
        }
        if (parent == -1 && children > 1) isArt[u] = true;
    }

    void findBridgesAndArticulation()
    {
        disc.assign(N + 1, 0);
        lowB.assign(N + 1, 0);
        visB.assign(N + 1, false);
        isArt.assign(N + 1, false);
        bridges.clear();
        dfsTime = 0;
        for (int i = 1; i <= N; i++)
            if (!visB[i]) dfsBrAP(i, -1);
    }
};
