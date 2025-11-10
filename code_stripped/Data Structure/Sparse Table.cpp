struct sparse_table
{
// for converting 1 based indexing initialize n=size+1,s[0]=dummy;
ll mxn;
ll k;
vector<vector<ll>> table1, table2;
vector<ll> logs;
sparse_table(ll n)
{
mxn = n;
logs.resize(n + 1, 0);
for (int i = 2; i <= mxn; i++)
{
logs[i] = logs[i >> 1] + 1;
}
k = logs[mxn] + 1;
table1.resize(mxn + 1, vector<ll>(k));
table2.resize(mxn + 1, vector<ll>(k));
}
void create_table(vector<ll> &v)
{
for (int i = 0; i < mxn; i++)
{
table1[i][0] = table2[i][0] = v[i];
}
for (ll i = 1; i < k; i++)
{
for (ll j = 0; j + (1 << i) - 1 < mxn; j++)
{
table1[j][i] = min(table1[j][i - 1], table1[j + (1 << (i - 1))][i - 1]);
table2[j][i] = max(table2[j][i - 1], table2[j + (1 << (i - 1))][i - 1]);
}
}
}
ll query1(ll x, ll y)
{
ll gap = y - x + 1;
ll lg = logs[gap];
return min(table1[x][lg], table1[y - (1 << lg) + 1][lg]);
}
ll query2(ll x, ll y)
{
ll gap = y - x + 1;
ll lg = logs[gap];
return max(table2[x][lg], table2[y - (1 << lg) + 1][lg]);
}
};