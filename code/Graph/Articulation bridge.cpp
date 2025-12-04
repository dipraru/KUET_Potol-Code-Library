const int N=1e4+5;
vector<int> g[N];
int timer;
int vis[N],dis[N],lo[N];
vector<pair<int,int>> ans;
void dfs(int src, int par)
{
    vis[src]=1,dis[src]=lo[src]=timer++;
    for(auto it:g[src])
    {
        if(it==par) continue;
        if(vis[it]) lo[src]=min(lo[src],dis[it]);
        else
        {
            dfs(it,src);
            lo[src]=min(lo[src],lo[it]);
            if(lo[it]>dis[src]) ans.push_back({min(it,src), max(it,src)});
        }
    }
}