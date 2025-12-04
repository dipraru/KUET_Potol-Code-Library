const int N=1505;
vector<int> g[N];
signed main()
{
    fast
    int n=1500;
    bitset<N> bit[n+1];
    for(int i=1;i<=n;i++){
        cin >> bit[i];
    }
    vector<int> pivot(n+1,-1);
    int basis[N];
    for(int i=1501;i>=0;i--)
    {
        int in=-1;
        for(int j=1;j<=n;j++)
        {
            if(pivot[j]==-1) continue;
            if(in!=-1 && bit[j][i]) bit[j]^=bit[in], g[j].push_back(in); 
            else if(bit[j][i]) in=j,pivot[j]=i, basis[i]=j;
        }
    }
    return 0;
}