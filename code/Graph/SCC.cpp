vector<vector<int>>g,rg;
vector<bool>vis;
int timer;
int stime[N];
int etime[N];
void dfs(int node)
{
    if(vis[node])return;
    vis[node]=1;
    stime[node]=++timer;
    for(auto it:g[node])
    {
        dfs(it);
    }
    etime[node]=++timer;
}
void rdfs(int node,vector<int>&tem)
{
    if(vis[node])return;
    vis[node]=1;
    tem.push_back(node);
    for(auto it:rg[node])
    {
        rdfs(it,tem);
    }
}
//main
int main()
{
    int n,m;
    cin>>n>>m;
    g.assign(n+1,vector<int>(0));
    rg.assign(n+1,vector<int>(0));
    vis.assign(n+1,0);
    timer=0;
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        rg[y].push_back(x);
    }
    vector<pair<int,int>>str;
    for(int i=1;i<=n;i++)
    {
        dfs(i);
        str.push_back({etime[i],i});
    }
    sort(all(str));
    reverse(all(str));
    vis.assign(n+1,0);
    for(auto [ww,i]:str)
    {
        if(vis[i])continue;
        vector<int>tem;
        rdfs(i,tem);
        for(auto it:tem)cout<<it<<" "; cout<<"\n";
    }
}
