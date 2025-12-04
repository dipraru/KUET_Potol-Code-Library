#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

ll modpow(ll a, ll e, ll mod)
{
    ll r = 1;
    a %= mod;
    while (e)
    {
        if (e & 1) r = (i128)r * a % mod;
        a = (i128)a * a % mod;
        e >>= 1;
    }
    return r;
}
ll modinv(ll a, ll mod) { return modpow((a % mod + mod) % mod, mod - 2, mod); }

struct XOR
{
    static inline void fwd(ll &u, ll &v)
    {
        ll x = u + v, y = u - v;
        u = x;
        v = y;
    }
    static inline void inv(ll &u, ll &v)
    {
        ll x = u + v, y = u - v;
        u = x;
        v = y;
    }
};
struct OR
{
    static inline void fwd(ll &u, ll &v) { v += u; }
    static inline void inv(ll &u, ll &v) { v -= u; }
};
struct AND
{
    static inline void fwd(ll &u, ll &v) { u += v; }
    static inline void inv(ll &u, ll &v) { u -= v; }
};

template <class Op>
void fwht(vector<ll> &a, bool invflag = false)
{
    int n = (int)a.size();
    for (int len = 1; len < n; len <<= 1)
    {
        for (int i = 0; i < n; i += len << 1)
        {
            for (int j = 0; j < len; ++j)
            {
                ll &x = a[i + j], &y = a[i + j + len];
                if (!invflag) Op::fwd(x, y);
                else Op::inv(x, y);
            }
        }
    }
    if (invflag && is_same<Op, XOR>::value)
        for (int i = 0; i < n; ++i) a[i] /= n;
}

template <class Op>
void fwht_mod(vector<ll> &a, ll mod, bool invflag = false)
{
    int n = (int)a.size();
    for (int len = 1; len < n; len <<= 1)
    {
        for (int i = 0; i < n; i += len << 1)
        {
            for (int j = 0; j < len; ++j)
            {
                ll x = a[i + j], y = a[i + j + len];
                if (!invflag)
                {
                    if constexpr (is_same<Op, XOR>::value)
                    {
                        ll nx = (x + y) % mod, ny = (x - y) % mod;
                        if (ny < 0) ny += mod;
                        a[i + j] = nx;
                        a[i + j + len] = ny;
                    }
                    else if constexpr (is_same<Op, OR>::value)
                        a[i + j + len] = (y + x) % mod;
                    else a[i + j] = (x + y) % mod;
                }
                else
                {
                    if constexpr (is_same<Op, XOR>::value)
                    {
                        ll nx = (x + y) % mod, ny = (x - y) % mod;
                        if (ny < 0) ny += mod;
                        a[i + j] = nx;
                        a[i + j + len] = ny;
                    }
                    else if constexpr (is_same<Op, OR>::value)
                    {
                        ll ny = (y - x) % mod;
                        if (ny < 0) ny += mod;
                        a[i + j + len] = ny;
                    }
                    else
                    {
                        ll nx = (x - y) % mod;
                        if (nx < 0) nx += mod;
                        a[i + j] = nx;
                    }
                }
            }
        }
    }
    if (invflag && is_same<Op, XOR>::value)
    {
        ll invn = modinv(n, mod);
        for (int i = 0; i < n; ++i)
            a[i] = (a[i] * (i128)invn) % mod;
    }
}

template <class Op>
vector<ll> conv(vector<ll> a, vector<ll> b)
{
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n <<= 1;
    a.resize(n);
    b.resize(n);
    fwht<Op>(a, false);
    fwht<Op>(b, false);
    for (int i = 0; i < n; ++i) a[i] = a[i] * b[i];
    fwht<Op>(a, true);
    return a;
}


template <class Op>
vector<ll> conv_mod(vector<ll> a, vector<ll> b, ll mod)
{
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n <<= 1;
    a.resize(n);
    b.resize(n);
    fwht_mod<Op>(a, mod, false);
    fwht_mod<Op>(b, mod, false);
    vector<ll> c(n);
    for (int i = 0; i < n; ++i)
        c[i] = (i128)a[i] * b[i] % mod;
    fwht_mod<Op>(c, mod, true);
    return c;
}

// quick usage demo
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // XOR integer conv
    {
        vector<ll> A = {1, 2, 3, 4}, B = {5, 6, 7, 8};
        auto C = conv<XOR>(A, B);
        for (auto x : C)
            cout << x << ' ';
        cout << "\n";
    }

    // OR integer conv (size must be pow2)
    {
        vector<ll> A(8), B(8);
        A[0] = 1;
        A[1] = 2;
        B[0] = 3;
        B[4] = 1;
        auto C = conv<OR>(A, B);
        for (auto x : C)
            cout << x << ' ';
        cout << "\n";
    }

    // XOR modular conv
    {
        ll MOD = 1000000007;
        vector<ll> A = {1, 2, 3, 4}, B = {5, 6, 7, 8};
        auto C = conv_mod<XOR>(A, B, MOD);
        for (auto x : C)
            cout << x << ' ';
        cout << "\n";
    }
    return 0;
}
