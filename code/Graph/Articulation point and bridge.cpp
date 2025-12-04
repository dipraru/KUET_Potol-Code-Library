const int N=1e5+5;
vector<int> g[N];
int vis[N],dis[N],lo[N],isAP[N];
int timer;
vector<pair<int,int>> ans;
void dfs(int src, int par)
{
    int child = 0;
    vis[src] = true;
    dis[src] = lo[src] = ++timer;
    for (auto v : g[src]) {
        if (!vis[v]) {
            child++;
            dfs(v,src);
            lo[src] = min(lo[src], lo[v]);
            if (par != -1 && lo[v] >= dis[src]) isAP[src] = true;
            if(lo[v]>dis[src]) ans.push_back({min(v,src), max(v,src)});
        }
        else if (v != par) lo[src] = min(lo[src], dis[v]);
    }
    if (par == -1 && child > 1) isAP[src] = true;
}