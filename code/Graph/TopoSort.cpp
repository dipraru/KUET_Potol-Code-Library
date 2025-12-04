vector<vector<int>>g;
vector<int>toposort(int n)
{
    queue<int>str;
    vector<int>in(n+1,0);
    for(int i=1;i<=n;i++)
    {
        for(auto it:g[i])in[it]++;
    }
    for(int i=1;i<=n;i++)if(in[i]==0)str.push(i);
    vector<int>ans;
    while(!str.empty())
    {
        auto x=str.front();
        str.pop();
        ans.push_back(x);
        for(auto it:g[x])
        {
            in[it]--;
            if(in[it]==0)str.push(it);
        }
    }
    return ans;
}
//g.resize(n+1,vector<int>(0));
//if(ans.size()!=n)cout<<"-1\n";