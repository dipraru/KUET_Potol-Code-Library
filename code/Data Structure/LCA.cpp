const int N=3e5+2;
vector<int>g[N];
int timer;
int stime[N];
int etime[N];
int pp[N][20];
void dfs(int node,int par)
{
    stime[node]=++timer;
    pp[node][0]=par;
    for(int i=1;i<20;i++)pp[node][i]=pp[pp[node][i-1]][i-1];
    for(auto it:g[node])
    {
        if(it==par)continue;
        dfs(it,node);
    }
    etime[node]=++timer;
}
int isansistor(int x,int y)
{
    if(x==0)return 1;
    return stime[x]<=stime[y]&&etime[x]>=etime[y];
}
int lca(int x,int y)
{
    if(stime[x]>stime[y])swap(x,y);
    if(isansistor(x,y))return x;
    for(int i=19;i>=0;i--)
    {
        int tem=pp[x][i];
        if(isansistor(tem,y)==0)
        {
            x=tem;
        }
    }
    return pp[x][0];
}
