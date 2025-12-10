const ll MLOG = 20;
const ll MAXN = (1<<MLOG);
ll dp[MAXN]; ll freq[MAXN];
void forward1(){ // adding element to all its super set
    for(ll bit = 0; bit < MLOG; bit++){
        for(ll i = 0; i < MAXN; i++){
            if(i&(1<<bit)){
                dp[i]+=dp[i^(1<<bit)]; //add a[i] to a[j] if j&i = i
            }
        }
    }
}
void backward1(){
    for(ll bit = 0; bit < MLOG; bit++){
        for(ll i = MAXN-1; i >= 0; i--){
            if(i&(1<<bit)){
                dp[i]-=dp[i^(1<<bit)];
            }
        }
    }
}
void forward2(){ // add elements to its subsets
    for(ll bit = 0; bit < MLOG; bit++){
        for(ll i = MAXN-1; i >= 0; i--){
            if(i&(1<<bit)){
                dp[i^(1<<bit)]+=dp[i];
            }
        }
    }
}
void backward2(){
    for(ll bit = 0; bit < MLOG; bit++){
        for(ll i = 0; i < MAXN; i++){
            if(i&(1<<bit)){
                dp[i^(1<<bit)]-=dp[i];
            }
        }
    }
}

//F[i] = A[i]2 +(SUM(G[j]))2 where (i&j) = j and j < i
//G[i] = (SUM(F[j]2)) where (i&j) = j and j <= i
int main()
{
    fastio
    int n;
    cin>>n;
    ll a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    int lg=log2(n)+2;
    ll f[n],g[n],gs[n][lg],f2s[n][lg];
    for(int i=0;i<n;i++)
    {
        f[i]=0;
        for(int j=0;j+1<lg;j++)
        {
            if(i&(1<<j))
            {
                f[i]=f[i]+gs[i^(1<<j)][j];
            }
        }
        f[i]%=M;
        f[i]=(f[i]*f[i]+a[i]*a[i])%M;
        f2s[i][0]=f[i]*f[i]%M;
        for(int j=0;j+1<lg;j++)
        {
            if(i&(1<<j))
            {
                f2s[i][j+1]=(f2s[i][j]+f2s[(i^(1<<j))][j])%M;
            }else f2s[i][j+1]=f2s[i][j];
        }
        g[i]=f2s[i][lg-1];
        gs[i][0]=g[i];
        for(int j=0;j+1<lg;j++)
        {
            if(i&(1<<j))
            {
                gs[i][j+1]=(gs[i][j]+gs[i^(1<<j)][j])%M;
            }else gs[i][j+1]=gs[i][j];
        }
    }
    ll sum=0;
    for(int i=0;i<n;i++)
    {
        sum=(sum+(f[i]*g[i]%M)*i)%M;
    }
    cout<<sum<<"\n";
}
