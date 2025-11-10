#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct numth
{

    // Struct to hold results of the Extended Euclidean Algorithm
    struct exgcd
    {
        ll gcd, x, y; // gcd of a and b, coefficients x and y for the equation ax + by = gcd(a, b)
    };

    // Extended Euclidean Algorithm to solve ax + by = gcd(a, b)
    exgcd exEuclid(ll a, ll b)
    {
        if (b == 0)
        {
            exgcd nd = {a, 1, 0};
            return nd;
        }
        exgcd sml = exEuclid(b, a % b);
        exgcd bg = {sml.gcd, sml.y, sml.x - (a / b) * sml.y};
        return bg;
    }
    ll gcd(ll a, ll b)
    {
        while (b != 0)
        {
            ll temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    ll lcm(ll a, ll b)
    {
        return (a / gcd(a, b)) * b;
    }
    ll multiInverse(ll a, ll m)
    {
        exgcd sml = exEuclid(a, m);
        if (sml.gcd != 1)
        {
            return -1;
        }
        return (sml.x % m + m) % m;
    }
    ll modInverseFermatsMethod(ll a, ll m)
    {
        ll inv = __gcd(a, m);
        if (inv != 1)
        {
            return -1;
        }
        return binaryExpo(a, m - 2, m);
    }

    ll modMul(ll a, ll b, ll m)
    {
        ll result = 0;
        a = a % m;
        while (b > 0)
        {
            if (b % 2 == 1)
            {
                result = (result + a) % m;
            }
            a = (a * 2) % m;
            b = b / 2;
        }
        return result;
    }
    ll binaryExpo(ll a, ll b, ll m)
    {
        ll result = 1;
        a = a % m;
        while (b > 0)
        {
            if (b % 2 == 1)
            {
                result = (result * a) % m;
                // result = modMul(result, a, m);
            }
            a = (a * a) % m;
            // a = modMul(a, a, m);
            b = b / 2;
        }

        return result;
    }
    vector<ll> svp;
    vector<ll> svl;
    bitset<200005> check;
    void sieve()
    {
        ll n = 2e5 + 2;
        check.reset();
        check[1] = 1;
        svl.resize(n + 2);
        for (int i = 4; i < n; i += 2)
        {
            check[i] = 1;
            svl[i] = 2;
        }
        for (ll i = 3; i * i < n; i += 2)
        {
            if (!check[i])
            {
                svl[i] = i;
                for (ll j = i * i; j < n; j += 2 * i)
                {
                    if (!check[j])
                    {
                        check[j] = 1;
                        svl[j] = i;
                    }
                }
            }
        }
        svp.push_back(2);
        svl[2] = 2;
        for (int i = 3; i < n; i += 2)
        {
            if (!check[i])
            {
                svp.push_back(i);
                svl[i] = i;
            }
        }
    }
    vector<pair<ll, ll>> primeFactorization(ll n)
    {
        vector<pair<ll, ll>> factors;
        while (n != 1)
        {
            ll prime = svl[n];
            ll count = 0;
            while (n % prime == 0)
            {
                n /= prime;
                count++;
            }
            factors.push_back({prime, count});
        }
        return factors;
    }
    vector<pair<ll, ll>> prime_factors(ll n)
    {
        vector<pair<ll, ll>> factors;
        int count = 0;
        while (n % 2 == 0)
        {
            n /= 2;
            count++;
        }
        if (count > 0)
        {
            factors.push_back(make_pair(2, count));
        }
        for (int i = 3; i <= sqrt(n); i += 2)
        {
            count = 0;
            while (n % i == 0)
            {
                n /= i;
                count++;
            }
            if (count > 0)
            {
                factors.push_back(make_pair(i, count));
            }
        }
        if (n > 2)
        {
            factors.push_back(make_pair(n, 1));
        }

        return factors;
    }
    vector<ll> findDivisors(ll n)
    {
        vector<ll> divisors;
        for (ll i = 1; i <= sqrt(n); ++i)
        {
            if (n % i == 0)
            {
                divisors.push_back(i);
                if (i != n / i)
                {
                    divisors.push_back(n / i);
                }
            }
        }
        sort(divisors.begin(), divisors.end());
        return divisors;
    }

    vector<pair<ll, ll>> primeFactorizationLarge(ll n)
    {
        vector<pair<ll, ll>> factors;

        for (ll i = 0; i < svp.size() && svp[i] * svp[i] <= n; ++i)
        {
            ll prime = svp[i];
            if (n % prime == 0)
            {
                ll count = 0;
                while (n % prime == 0)
                {
                    n /= prime;
                    count++;
                }
                factors.push_back({prime, count});
            }
        }
        if (n > 1)
        {
            factors.push_back({n, 1});
        }
        return factors;
    }
    vector<ll> segmented_sieve(ll l, ll r)
    {
        vector<ll> segpr;
        vector<bool> pr(r - l + 5, 1);
        if (l == 1)
        {
            pr[0] = false;
        }
        for (ll i = 0; svp[i] * svp[i] <= r; i++)
        {
            ll cur = svp[i];
            ll base = cur * cur;
            if (base < l)
            {
                base = ((l + cur - 1) / cur) * cur;
            }
            for (ll j = base; j <= r; j += cur)
            {
                pr[j - l] = false;
            }
        }
        for (ll i = 0; i <= r - l; i++)
        {
            if (pr[i] == 1)
            {
                segpr.push_back(l + i);
            }
        }
        return segpr;
    }
    ll eulerTotientFunction(ll n)
    {
        ll result = n;
        for (ll i = 0; i < svp.size() && svp[i] * svp[i] <= n; ++i)
        {
            if (n % svp[i] == 0)
            {
                while (n % svp[i] == 0)
                {
                    n /= svp[i];
                }
                result -= result / svp[i];
            }
        }
        if (n > 1)
        {
            result -= result / n;
        }
        return result;
    }
    vector<ll> computeTotientUpToN(ll n)
    {
        vector<ll> phi(n + 1);
        for (ll i = 1; i <= n; ++i)
        {
            phi[i] = i;
        }
        for (ll i = 2; i <= n; ++i)
        {
            if (phi[i] == i)
            {
                for (ll j = i; j <= n; j += i)
                {
                    phi[j] *= (i - 1);
                    phi[j] /= i;
                }
            }
        }
        return phi;
    }
    ll sumOfDivisors(ll n)
    {
        vector<pair<ll, ll>> factors = primeFactorizationLarge(n);
        ll sum = 1;
        for (auto &factor : factors)
        {
            ll p = factor.first;
            ll a = factor.second;
            ll term = 1;
            for (ll i = 0; i <= a; i++)
            {
                term *= p;
            }
            sum *= (term - 1) / (p - 1);
        }
        return sum;
    }
    ll sumOfDivisors(ll n, ll mod = 1e9 + 7)
    {
        vector<pair<ll, ll>> factors = primeFactorizationLarge(n);
        ll sum = 1;
        for (auto &factor : factors)
        {
            ll p = factor.first;
            ll a = factor.second;
            ll term = binaryExpo(p, a + 1, mod);
            term = (term - 1 + mod) % mod;
            ll inv = multiInverse(p - 1, mod);
            term = (term * inv) % mod;
            sum = (sum * term) % mod;
        }
        return sum;
    }
    ll numberOfDivisors(ll n)
    {
        vector<pair<ll, ll>> factors = primeFactorizationLarge(n);
        ll count = 1;
        for (auto &factor : factors)
        {
            count *= (factor.second + 1);
        }
        return count;
    }
    ll chineseRemainderTheorem(vector<ll> nums, vector<ll> rems)
    {
        ll prod = accumulate(nums.begin(), nums.end(), 1LL, multiplies<ll>());
        ll result = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            ll pp = prod / nums[i];
            result += rems[i] * multiInverse(pp, nums[i]) * pp;
        }
        return result % prod;
    }
};
