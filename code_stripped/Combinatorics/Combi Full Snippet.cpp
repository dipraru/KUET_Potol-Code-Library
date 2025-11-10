struct combi
{
typedef long long ll;
const ll md = 1e20;
ll add(ll a, ll b)
{
ll res = (a + b) % md;
return res+(res<0)*md;
}
ll mul(ll a, ll b)
{
ll res = (a * b) % md;
return res+(res<0)*md;
}
ll modpw(ll a, ll b)
{
if (b == 0) return 1 % md;
ll v = modpw(a, b / 2);
v = mul(v, v);
if (b % 2 == 1) v = mul(v, a);
return v;
}
vector<ll> facts,invs,finvs,derangements;
vector<vector<ll>> stirling_second,stirling_first;
int sz;
void init(int n)
{
sz = n;
facts.assign(n + 1, 1);
invs.assign(n + 1, 1);
finvs.assign(n + 1, 1);
for (int i = 2; i <= n; i++) invs[i] = modpw(i, md - 2);
for (int i = 1; i <= n; i++)facts[i] = mul(facts[i - 1], i),finvs[i] = mul(finvs[i - 1], invs[i]);
}
void init_derangement(int n)
{
sz = n;
derangements.assign(n + 1, 0);
derangements[0] = 1,derangements[1] = 0;
for (int i = 2; i <= n; i++) derangements[i] = mul(i - 1, add(derangements[i - 1], derangements[i - 2]));
}
void init_stirlingSecond(int n)
{
sz = n;
stirling_second.assign(n + 1, vector<ll>(n + 1, 0));
stirling_second[0][0] = 1;
for (int i = 1; i <= n; i++)
for (int j = 1; j <= i; j++) stirling_second[i][j] = add(mul(j, stirling_second[i - 1][j]), stirling_second[i - 1][j - 1]);
}
void init_stirlingFirst(int n)
{
sz = n;
stirling_first.assign(n + 1, vector<ll>(n + 1, 0));
stirling_first[0][0] = 1;
for (int i = 1; i <= n; i++)
for (int j = 1; j <= i; j++)stirling_first[i][j] = add(mul(i - 1, stirling_first[i - 1][j]), stirling_first[i - 1][j - 1]);
}
ll fact(int n){return facts[n];}
ll inv(int n){return invs[n];}
ll finv(int n){return finvs[n];}
ll ncr(int n, int r)
{
if (r > n || r < 0)return 0;
return mul(facts[n], mul(finvs[r], finvs[n - r]));
}
ll npr(int n, int r)
{
if (r > n || r < 0)return 0;
return mul(facts[n], finvs[n - r]);
}
ll catalan(int n)
{
if (n == 0)return 1;
return mul(ncr(2 * n, n), inv(n + 1));
}
ll multinomial(const vector<int> &counts)
{
ll sum = 0;
for (int count : counts)sum = add(sum, count);
ll result = fact(sum);
for (int count : counts)result = mul(result, finv(count));
return result;
}
ll derangement(ll n){return derangements[n];}
ll stirlingSecond(int n, int k){return stirling_second[n][k];}
ll stirlingFirst(int n, int k){return stirling_first[n][k];}
};
