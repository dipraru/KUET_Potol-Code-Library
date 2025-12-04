using ll = long long;

struct WaveletTree
{
    int lo, hi;
    WaveletTree *L = nullptr, *R = nullptr;
    // b[i] = number of elements from prefix[0..i-1] that went to left child.
    // b.size() == n+1 where b[0] = 0.
    vector<int> b;
    // optional: prefix sum of original values for range-sum queries
    vector<ll> pref; // pref[0] = 0, pref[i] = sum of first i original elements

    WaveletTree() = default;

    // construct from array 'arr' with values in range [x, y]
    WaveletTree(const vector<int> &arr, int x, int y) : lo(x), hi(y), L(nullptr), R(nullptr)
    {
        int n = (int)arr.size();
        b.reserve(n + 1);
        pref.reserve(n + 1);
        b.push_back(0);
        pref.push_back(0);
        if (n == 0)
            return;
        if (lo == hi)
        {
            // all values equal to lo
            for (int v : arr)
            {
                b.push_back(b.back() + 1); // all go left conceptually
                pref.push_back(pref.back() + v);
            }
            return;
        }
        int mid = (lo + hi) >> 1;
        vector<int> leftArr;
        leftArr.reserve(n);
        vector<int> rightArr;
        rightArr.reserve(n);
        for (int v : arr)
        {
            if (v <= mid)
            {
                leftArr.push_back(v);
                b.push_back(b.back() + 1);
            }
            else
            {
                rightArr.push_back(v);
                b.push_back(b.back());
            }
            pref.push_back(pref.back() + v);
        }
        if (!leftArr.empty())
            L = new WaveletTree(leftArr, lo, mid);
        if (!rightArr.empty())
            R = new WaveletTree(rightArr, mid + 1, hi);
    }

    ~WaveletTree()
    {
        delete L;
        delete R;
    }

    // ----------------- Queries -----------------
    // kth smallest in [l, r], 1-based. returns -1 if invalid k.
    int kth(int l, int r, int k) const
    {
        if (l > r || k <= 0 || k > r - l + 1) return -1;
        if (lo == hi) return lo;
        int inLeft = b[r] - b[l - 1];
        if (k <= inLeft) return L->kth(b[l - 1] + 1, b[r], k);
        else return R->kth(l - b[l - 1], r - b[r], k - inLeft);
    }

    // count of numbers <= k in [l, r]
    int countLTE(int l, int r, int k) const
    {
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return (L ? L->countLTE(lb + 1, rb, k) : 0) + (R ? R->countLTE(l - lb, r - rb, k) : 0);
    }

    // count equal to value in [l, r]
    int countEqual(int l, int r, int value) const
    {
        if (l > r || value < lo || value > hi) return 0;
        if (lo == hi) return r - l + 1;
        int mid = (lo + hi) >> 1;
        int lb = b[l - 1], rb = b[r];
        if (value <= mid) return L ? L->countEqual(lb + 1, rb, value) : 0;
        else return R ? R->countEqual(l - lb, r - rb, value) : 0;
    }

    // sum of values < k in [l, r]
    // Requires pref to be present (we store original prefix sums at construction)
    ll sumLess(int l, int r, int k) const
    {
        if (l > r || k <= lo) return 0;
        if (hi < k) return pref[r] - pref[l - 1];
        int lb = b[l - 1], rb = b[r];
        ll leftSum = L ? L->sumLess(lb + 1, rb, k) : 0;
        ll rightSum = R ? R->sumLess(l - lb, r - rb, k) : 0;
        return leftSum + rightSum;
    }

    // utility: returns total number of elements stored at this node
    int size() const
    {
        return (int)pref.size() - 1;
    }
};
