#include <bits/stdc++.h>
using namespace std;
#define fast {ios_base::sync_with_stdio(false); cin.tie(0);}
typedef long long ll;
#define int long long
#define float long double
int cs;
const int N=1e4+5;
vector<int> g[N];
int vis[N],dis[N],lo[N],isAP[N];
int timer;
set<pair<int,int>> ans;
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
        }
        else if (v != par) lo[src] = min(lo[src], dis[v]);
    }
    if (par == -1 && child > 1) isAP[src] = true;
}
void solve()
{
    int n,m,c=0;
    timer=1;
    cin >> n >> m;
    for(int i=0;i<=n;i++) g[i].clear(), vis[i]=dis[i]=lo[i]=isAP[i]=0;
    for(int i=0,u,v;i<m;i++) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,-1);
    for(int i=1;i<=n;i++) if(isAP[i]) cout << i << ' ';
    cout <<'\n';
}
signed main()
{
    fast
    int t=1;
    cin >> t;
    for(cs=1;cs<=t;cs++)
    {
        cout << "Case " << cs << ": "; 
        solve();
    }
    return 0;
}