vector<pair<int,int>>suflcp(vector<int>ss)//string s -- vector<int>s (both works)
{
    int n=ss.size();
    //ranking elements
    auto s=ss;
    vector<pair<int,int>>rnk;
    //map<int,vector<int>>rnk;
    for(int i=0; i<n; i++) rnk.push_back({s[i],i});
    sort(all(rnk));
    int pre=-1,prev=-M;
    for(auto it:rnk)
    {
        if(it.first!=prev)pre++,prev=it.first;
        s[it.second]=pre;
    }//ranking ends
    int q=1,co=1;
    while(q<n)co++,q*=2;
    int tra[n][co];
    vector<pair<pair<int,int>,int>>str,tem[n+3];
    for(int i=0; i<n; i++) str.push_back({{s[i],-1},i});
    //sort(all(str));
    for(int i=0; i<n; i++) tem[str[i].first.second+1].push_back(str[i]);
    str.clear();
    for(int i=0; i<n+3; i++)
    {
        for(auto it:tem[i])str.push_back(it);
        tem[i].clear();
    }
    for(int i=0; i<n; i++) tem[str[i].first.first+1].push_back(str[i]);
    str.clear();
    for(int i=0; i<n+3; i++)
    {
        for(auto it:tem[i])str.push_back(it);
        tem[i].clear();
    }
    //sort end
    int k=-1;
    pair<int,int>p= {-inf,-inf};
    for(auto it:str)
    {
        if(it.first!=p)k++,p=it.first;
        tra[it.second][0]=k;
    }
    q=1;
    for(int i=1; i<co; i++)
    {
        str.clear();
        for(int j=0; j<n; j++)
        {
            if(j+q>=n) str.push_back({{tra[j][i-1],-1},j});
            else str.push_back({{tra[j][i-1],tra[j+q][i-1]},j});
        }
        //sort(all(str));
        for(int i=0; i<n; i++) tem[str[i].first.second+1].push_back(str[i]);
        str.clear();
        for(int i=0; i<n+3; i++)
        {
            for(auto it:tem[i])str.push_back(it);
            tem[i].clear();
        }
        for(int i=0; i<n; i++) tem[str[i].first.first+1].push_back(str[i]);
        str.clear();
        for(int i=0; i<n+3; i++)
        {
            for(auto it:tem[i])str.push_back(it);
            tem[i].clear();
        }
        //sort end
        int k=-1;
        pair<int,int>p= {-inf,-inf};
        for(auto it:str)
        {
            if(it.first!=p)k++,p=it.first;
            tra[it.second][i]=k;
        }
        q*=2;
    }
    vector<pair<int,int>>ans(n);
    for(int i=0; i<n; i++) ans[tra[i][co-1]].first=i;
    //lcp calculation
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)rank[ans[i].first] = i;
    k = 0;
    //vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = ans[rank[i] + 1].first;
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        ans[rank[i]].second = k;
        if (k) k--;
    }
    return ans; //ans[n-1].second=0;
}
vector<pair<int,int>>suflcp(string ss)
{
    int n=ss.size();
    vector<int>sss;
    for(int i=0;i<n;i++)sss.push_back(ss[i]);
    return suflcp(sss);
}