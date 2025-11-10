#include <bits/stdc++.h>
using namespace std;

struct SegTree
{
    struct Node
    {
        long long v;
        Node() : v(0) {}
        Node(long long _v) : v(_v) {}
    };

    int n;
    vector<Node> tre;

    SegTree(int sz = 0)
    {
        init(sz);
    }

    void init(int _n)
    {
        n = 1;
        while (n < _n)
            n <<= 1;
        tre.assign(2 * n, Node());
    }

    Node merge(const Node &L, const Node &R) const
    {
        return Node(L.v + R.v);
    }

    void build(const vector<long long> &a)
    {
        int orig = a.size();
        init(orig);
        for (int i = 0; i < orig; i++)
        {
            tre[n + i] = Node(a[i]);
        }
        for (int i = n - 1; i >= 1; i--)
        {
            tre[i] = merge(tre[2 * i], tre[2 * i + 1]);
        }
    }

    void update(int p, long long val)
    {
        int idx = p + n;
        tre[idx] = Node(val);
        idx >>= 1;
        while (idx >= 1)
        {
            tre[idx] = merge(tre[2 * idx], tre[2 * idx + 1]);
            idx >>= 1;
        }
    }

    Node rangeQuery(int l, int r) const
    {
        if (l > r)
            return Node();
        int L = l + n, R = r + n;
        Node resL = Node(), resR = Node();
        while (L <= R)
        {
            if (L & 1)
            {
                resL = merge(resL, tre[L]);
                L++;
            }
            if (!(R & 1))
            {
                resR = merge(tre[R], resR);
                R--;
            }
            L >>= 1;
            R >>= 1;
        }
        return merge(resL, resR);
    }

    long long query(int l, int r) const
    {
        return rangeQuery(l, r).v;
    }

    long long get(int p) const
    {
        return tre[n + p].v;
    }
};
