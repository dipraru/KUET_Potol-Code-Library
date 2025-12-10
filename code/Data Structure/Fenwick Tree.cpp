struct FenwickTree
{
    vector<int> tree;
    int n;
    FenwickTree(int n){this->n = n,tree.resize(n + 1, 0);}
    void update(int idx, int val)
    {
        while (idx <= n)tree[idx] += val,idx += idx & (-idx);
    }
    int query(int idx)
    {
        int sum = 0;
        while (idx > 0)sum += tree[idx],idx -= idx & (-idx);
        return sum;
    }
    int rangeQuery(int l, int r){ return query(r) - query(l - 1);}
    int inversion_count(vector<int> &arr)
    {
        int icount = 0;
        for (int i = n; i > 0; i--)
        {
            int smallerCount = query(arr[i] - 1);
            icount += smallerCount;
            update(arr[i], 1);
        }
        return icount;
    }
    
    int kth(int k)
    {
        if (k <= 0 || query(n) < k) return -1;
        int idx = 0, mask = 1 << (31 - __builtin_clz(n));
        int acc = 0;
        while (mask)
        {
            int next = idx + mask;
            if (next <= n && acc + tree[next] < k)
            {
                idx = next;
                acc += tree[next];
            }
            mask >>= 1;
        }
        return idx + 1;
    }
};