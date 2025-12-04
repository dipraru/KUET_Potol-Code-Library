*******************Offline **********************
// dpcur[i] depends on dppre[1--n]
const ll M = 1e16 + 7;
const ll N = 1e5 + 3;
ll dis[N];
ll xcross(ll m1, ll c1, ll m2, ll c2, ll n)
{
    ld ans = ((ld)c1 - c2) / (m2 - m1);
    if (ans > n) ans = n + 1;
    return ceil(ans);
}
// main
int main()
{
    fastio int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) dis[i] = M;
    for (ll i = 1; i <= k; i++)
    {
        vector<ll> str;
        str.push_back(1);
        str.push_back(2);
        for (ll i = 3; i <= n; i++)
        {
            while (str.size() > 1)
            {
                ll lst = str.back();
                ll slst = str[str.size() - 2];
                ll cur = xcross(-2 * lst, dis[lst] + lst * lst, -2 * i, dis[i] + i * i, n);
                ll pre = xcross(-2 * lst, dis[lst] + lst * lst, -2 * slst, dis[slst] + slst * slst, n);
                if (cur <= pre) str.pop_back();
                else break;
            }
            str.push_back(i);
        }
        ll pre = 1;
        ll diss[n + 1];
        for (ll i = 1; i < str.size(); i++)
        {
            ll lst = str[i];
            ll cur = xcross(-2 * lst, dis[lst] + lst * lst, -2 * i, dis[i] + i * i, n);
        }
        for (ll i = 1; i < str.size(); i++)
        {
            ll lst = str[i - 1];
            ll slst = str[i];
            ll cur = xcross(-2 * lst, dis[lst] + lst * lst, -2 * slst, dis[slst] + slst * slst, n);
            for (ll i = pre; i < cur; i++) diss[i] = (i - lst) * (i - lst) + dis[lst];
            pre = cur;
        }
        ll lst = str.back();
        for (ll i = pre; i <= n; i++) diss[i] = (i - lst) * (i - lst) + dis[lst];
        for (int i = 1; i <= n; i++) dis[i] = diss[i];
    }
    for (int i = 1; i <= n; i++) cout << dis[i] << " ";
    cout << "\n";
}

// for(i>j) dp[i]=min(dp[j]+(i-j)^2+c); [1]=C0;
ll xcross(ll m1, ll c1, ll m2, ll c2, ll n)
{
    ld ans = ((ld)c1 - c2) / (m2 - m1);
    if (ans > n) ans = n + 1;
    return ceil(ans);
}
ll dp[N];
void CHT(ll n, ll C1, ll C)
{
    dp[1] = C1;
    vector<ll> str;
    str.push_back(1);
    int cur = 0;
    for (ll i = 2; i <= n; i++)
    {
        dp[i] = C + (i - str[cur]) * (i - str[cur]) + dp[str[cur]];
        while (cur < (int)str.size() - 1)
        {
            cur++;
            ll tem = C + (i - str[cur]) * (i - str[cur]) + dp[str[cur]];
            if (tem > dp[i])
            {
                cur--;
                break;
            }
            dp[i] = tem;
        }
        while (str.size() > 1)
        {
            ll lst = str.back();
            ll slst = str[str.size() - 2];
            ll cur = xcross(-2 * lst, dp[lst] + lst * lst, -2 * i, dp[i] + i * i, n);
            ll pre = xcross(-2 * lst, dp[lst] + lst * lst, -2 * slst, dp[slst] + slst * slst, n);
            if (cur <= pre) str.pop_back();
            else break;
        }
        if (cur >= str.size()) cur = str.size() - 1;
        str.push_back(i);
    }
}
