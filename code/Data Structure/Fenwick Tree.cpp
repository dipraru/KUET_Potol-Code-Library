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
};