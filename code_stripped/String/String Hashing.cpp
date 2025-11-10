#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct SimpleHash
{
ll len;
ll base, mod;
vector<ll> P, H, R;
SimpleHash() {};
SimpleHash(string str, ll b, ll m)
{
base = b, mod = m, len = str.size();
P.resize(len + 4, 1), H.resize(len + 3, 0), R.resize(len + 3, 0);
for (ll i = 1; i <= len + 3; i++)
{
P[i] = (P[i - 1] * base) % mod;
}
for (ll i = 1; i <= len; i++)
{
H[i] = (H[i - 1] * base + str[i - 1] + 1007) % mod;
}
for (ll i = len; i >= 1; i--)
{
R[i] = (R[i + 1] * base + str[i - 1] + 1007) % mod;
}
}
ll range_hash(ll l, ll r)
{
ll hashval = H[r + 1] - ((ll)P[r - l + 1] * H[l] % mod);
return (hashval < 0 ? hashval + mod : hashval);
}
ll reverse_hash(ll l, ll r)
{
ll hashval = R[l + 1] - ((ll)P[r - l + 1] * R[r + 2] % mod);
return (hashval < 0 ? hashval + mod : hashval);
}
};
struct DoubleHash
{
SimpleHash sh1, sh2;
DoubleHash() {}
DoubleHash(string str)
{
sh1 = SimpleHash(str, 1949313259, 2091573227);
sh2 = SimpleHash(str, 1997293877, 2117566807);
}
long long range_hash(ll l, ll r)
{
return ((long long)sh1.range_hash(l, r) << 32) ^ sh2.range_hash(l, r);
}
long long reverse_hash(ll l, ll r)
{
return ((long long)sh1.reverse_hash(l, r) << 32) ^ sh2.reverse_hash(l, r);
}
};
