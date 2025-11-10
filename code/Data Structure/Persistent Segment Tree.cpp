#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Persistent
{
    struct Node
    {
        long long sum, min_val, max_val;
        Node *left, *right;

        Node() : sum(0), min_val(LLONG_MAX), max_val(LLONG_MIN), left(nullptr), right(nullptr) {}
    };

    Node *root;
    int n;

    Persistent(int n)
    {
        this->n = n;
        root = build(1, n);
    }

    Node *build(int st, int ed)
    {
        Node *node = new Node();
        if (st == ed)
        {
            return node;
        }
        int mid = (st + ed) / 2;
        node->left = build(st, mid);
        node->right = build(mid + 1, ed);
        return node;
    }

    Node merge(const Node &left, const Node &right)
    {
        Node result;
        result.sum = left.sum + right.sum;
        result.min_val = std::min(left.min_val, right.min_val);
        result.max_val = std::max(left.max_val, right.max_val);
        return result;
    }

    Node *update(Node *node, int st, int ed, int idx, long long val)
    {
        Node *nd = new Node(*node);
        if (st == ed)
        {
            nd->sum = val;
            nd->min_val = val;
            nd->max_val = val;
            return nd;
        }
        int mid = (st + ed) / 2;
        if (idx <= mid)
        {
            nd->left = update(node->left, st, mid, idx, val);
        }
        else
        {
            nd->right = update(node->right, mid + 1, ed, idx, val);
        }
        Node left_result = nd->left ? *(nd->left) : Node();
        Node right_result = nd->right ? *(nd->right) : Node();
        Node merged_result = merge(left_result, right_result);
        nd->sum = merged_result.sum;
        nd->min_val = merged_result.min_val;
        nd->max_val = merged_result.max_val;
        return nd;
    }

    Node query(Node *node, int st, int ed, int l, int r)
    {
        if (!node || st > r || ed < l)
        {
            return Node();
        }
        if (st >= l && ed <= r)
        {
            return *node;
        }
        int mid = (st + ed) / 2;
        Node left_result = query(node->left, st, mid, l, r);
        Node right_result = query(node->right, mid + 1, ed, l, r);
        return merge(left_result, right_result);
    }

    Node *updateIndex(Node *root, int idx, long long val)
    {
        return update(root, 1, n, idx, val);
    }

    Node queryRange(Node *root, int l, int r)
    {
        return query(root, 1, n, l, r);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }
    Persistent obj(n);
    Persistent::Node *root = obj.root;
    for (int i = 1; i <= n; i++)
    {
        root = obj.updateIndex(root, i, v[i]);
    }
    vector<Persistent::Node *> version;
    version.push_back(root);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            ll k, a, x;
            cin >> k >> a >> x;
            Persistent::Node *newRoot = obj.updateIndex(version[k - 1], a, x);
            version[k - 1] = newRoot;
        }
        else if (op == 2)
        {
            ll k, a, b;
            cin >> k >> a >> b;
            cout << obj.queryRange(version[k - 1], a, b).sum << endl;
        }
        else
        {
            int k;
            cin >> k;
            version.push_back(version[k - 1]);
        }
    }
}