vector<int>g[N];
int b[N],a[N];
int parent[N], depth[N], heavy[N], head[N], pos[N];
int timer=0;
int dfs(int node)
{
    int msi=0,si=1;
    heavy[node]=0;
    for(auto it:g[node])
    {
        if(it==parent[node])continue;
        parent[it]=node;
        depth[it]=depth[node]+1;
        int csi=dfs(it);
        si+=csi;
        if(csi>msi)
        {
            msi=csi;
            heavy[node]=it;
        }
    }
    return si;
}
void decompose(int node,int h)
{
    head[node]=h;
    timer++;
    pos[node]=timer;
    b[timer]=a[node];
    if(heavy[node]!=0)
    {
        decompose(heavy[node],h);
    }
    for(auto it:g[node])
    {
        if(it==parent[node]||it==heavy[node])continue;
        decompose(it,it);
    }
}
int query(int x,int y,int n)
{
    int res = 0;
    for (; head[x] != head[y]; y = parent[head[y]])
    {
    
        if (depth[head[x]] > depth[head[y]])swap(x, y);
        if(pos[y]-pos[head[y]]<=10)for(int i=pos[y]; i>=pos[head[y]]; i--)res=max(res,b[i]);
        else res=max(res,ans(1,1,n,pos[head[y]], pos[y]));
    }
    if (depth[x] > depth[y])swap(x, y);
    if(pos[y]-pos[x]<=10) for(int i=pos[y]; i>=pos[x]; i--)res=max(res,b[i]);
    else res=max(res,ans(1,1,n,pos[x], pos[y]));
    return res;
}