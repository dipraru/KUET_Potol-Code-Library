using ll = long long;
struct Node {
  ll a;
  Node() : a(LLONG_MIN/4) {}
  Node(ll _a) : a(_a) {}
  friend Node merge(const Node &A, const Node &B) {
    return Node(max(A.a, B.a));
  }
};

struct SegmentTree {
  int n;
  int size;
  vector<Node> t;
  vector<ll> lazy;
  vector<bool> isLazy;

  SegmentTree(int _n) { init(_n); }

  void init(int _n) {
    n = _n;
    size = 1;
    while (size < max(1, n)) size <<= 1;
    t.assign(2 * size, Node());
    lazy.assign(2 * size, 0);
    isLazy.assign(2 * size, 0);
  }

  void build(const vector<ll> &vals) {
    for (int i = 1; i <= n; ++i) t[size + i - 1] = Node(vals[i]);
    for (int i = n + 1; i <= size; ++i) t[size + i - 1] = Node();
    for (int nd = size - 1; nd >= 1; --nd) pull(nd);
  }

  inline void pull(int nd) {
    t[nd] = merge(t[nd << 1], t[nd << 1 | 1]);
  }
  inline void apply_node(int nd, int st, int en, ll val) {
    t[nd].a += val;
    lazy[nd] += val;
    isLazy[nd] = 1;
  }

  inline void push(int nd, int st, int en) {
    if (!isLazy[nd] || nd >= size) return;
    int mid = (st + en) >> 1;
    apply_node(nd << 1, st, mid, lazy[nd]);
    apply_node(nd << 1 | 1, mid+1, en, lazy[nd]);
    isLazy[nd] = 0;
    lazy[nd] = 0;
  }
  void update(int l, int r, ll val) { update(1, 1, size, l, r, val); }
  void update(int nd, int st, int en, int l, int r, ll val) {
    if (l > en || r < st) return;
    if (l <= st && en <= r) {
      apply_node(nd, st, en, val);
      return;
    }
    push(nd, st, en);
    int mid = (st + en) >> 1;
    update(nd << 1, st, mid, l, r, val);
    update(nd << 1 | 1, mid + 1, en, l, r, val);
    pull(nd);
  }

  Node query(int l, int r) { return query(1, 1, size, l, r); }
  Node query(int nd, int st, int en, int l, int r) {
    if (l > en || r < st) return Node();
    if (l <= st && en <= r) return t[nd];
    push(nd, st, en);
    int mid = (st + en) >> 1;
    Node L = query(nd << 1, st, mid, l, r);
    Node R = query(nd << 1 | 1, mid + 1, en, l, r);
    return merge(L, R);
  }
};
