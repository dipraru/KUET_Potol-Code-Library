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
    ll EuclidInverse(ll a, ll m)
    {
        exgcd sml = exEuclid(a, m);
        if (sml.gcd != 1)
        {
            return -1;
        }
        return (sml.x % m + m) % m;
    }

    vector<ll> svp;//all primes
    vector<ll> svl;//lowest prime
    bitset<200005> check;
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
    ll sumOfDivisors(ll n)
    {
        vector<pair<ll, ll>> factors = primeFactorization(n);
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
    ll CRT(vector<ll> nums, vector<ll> rems)
    {
        ll prod = accumulate(nums.begin(), nums.end(), 1LL, multiplies<ll>());
        ll result = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            ll pp = prod / nums[i];
            result += rems[i] * EuclidInverse(pp, nums[i]) * pp;
        }
        return result % prod;
    }
};
