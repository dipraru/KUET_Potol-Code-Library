struct HeavyLightDecomposition
{
using T = long long;
struct SegTree
{
struct Node
{
T sum;
Node() : sum(0) {}
Node(T val) : sum(val) {}
};
struct LazyNode
{
T value;
LazyNode() : value(0) {}
LazyNode(T val) : value(val) {}
};
vector<Node> tree;
vector<LazyNode> lazy;
int n;
SegTree(int n) : n(n)
{
tree.resize(4 * n + 5),lazy.resize(4 * n + 5);
}
Node merge(const Node &left, const Node &right){ return Node(left.sum + right.sum);}
void applyLazy(int nd, int st, int ed, const LazyNode &lz){tree[nd].sum += lz.value * (ed - st + 1);}
void propagateLazy(int nd, int st, int ed)
{
if (lazy[nd].value != 0)
{
applyLazy(nd, st, ed, lazy[nd]);
if (st != ed)lazy[2 * nd].value += lazy[nd].value.lazy[2 * nd + 1].value += lazy[nd].value;
lazy[nd] = LazyNode();
}
}
void build(int nd, int st, int ed, vector<T> &v)
{
if (st == ed){tree[nd] = Node(v[st]);return;}
int mid = (st + ed) / 2;
build(2 * nd, st, mid, v);
build(2 * nd + 1, mid + 1, ed, v);
tree[nd] = merge(tree[2 * nd], tree[2 * nd + 1]);
}
void build(vector<T> &v){ build(1, 1, n, v);}
void updateRange(int nd, int st, int ed, int l, int r, T val)
{
propagateLazy(nd, st, ed);
if (st > r || ed < l)return;
if (st >= l && ed <= r)
{
lazy[nd].value = val;
propagateLazy(nd, st, ed);
return;
}
int mid = (st + ed) / 2;
updateRange(2 * nd, st, mid, l, r, val);
updateRange(2 * nd + 1, mid + 1, ed, l, r, val);
tree[nd] = merge(tree[2 * nd], tree[2 * nd + 1]);
}
void update(int l, int r, T val){updateRange(1, 1, n, l, r, val);}
Node queryRange(int nd, int st, int ed, int l, int r)
{
propagateLazy(nd, st, ed);
if (st > r || ed < l)return Node();
if (st >= l && ed <= r)return tree[nd];
int mid = (st + ed) / 2;
Node leftQuery = queryRange(2 * nd, st, mid, l, r);
Node rightQuery = queryRange(2 * nd + 1, mid + 1, ed, l, r);
return merge(leftQuery, rightQuery);
}
T query(int l, int r){return queryRange(1, 1, n, l, r).sum;}
void updatePoint(int idx, T val){update(idx, idx, val);}
T queryPoint(int idx){return query(idx, idx);}
};
vector<vector<int>> adj;
vector<int> parent, depth, heavy, head, pos, subsize;
SegTree segTree;
int curPos;
HeavyLightDecomposition(int n)
: adj(n + 1),parent(n + 1, -1),depth(n + 1, 0),heavy(n + 1, -1),head(n + 1),pos(n + 1),subsize(n + 1, 0),segTree(n),curPos(1) {}
void addEdge(int u, int v){adj[u].push_back(v),adj[v].push_back(u);}
int dfs(int u)
{
subsize[u] = 1;
int maxSubtree = 0;
for (int v : adj[u])
{
if (v == parent[u])continue;
parent[v] = u,depth[v] = depth[u] + 1;
int subtreeSize = dfs(v);
subsize[u] += subtreeSize;
if (subtreeSize > maxSubtree)maxSubtree = subtreeSize,heavy[u] = v;
}
return subsize[u];
}
void decompose(int u, int h)
{
head[u] = h;
pos[u] = curPos++;
if (heavy[u] != -1)decompose(heavy[u], h);
for (int v : adj[u]) if (v != parent[u] && v != heavy[u])decompose(v, v);
}
void init(int root = 1){dfs(root),decompose(root, root);}
void updatePath(int u, int v, T value, bool isEdge = false)
{
while (head[u] != head[v])
{
if (depth[head[u]] < depth[head[v]])swap(u, v);
segTree.update(pos[head[u]], pos[u], value);
u = parent[head[u]];
}
if (depth[u] > depth[v])swap(u, v);
segTree.update(pos[u] + isEdge, pos[v], value);
}
T queryPath(int u, int v, bool isEdge = false)
{
T result = numeric_limits<T>::min();
while (head[u] != head[v])
{
if (depth[head[u]] < depth[head[v]])swap(u, v);
result = max(result, segTree.query(pos[head[u]], pos[u]));
u = parent[head[u]];
}
if (depth[u] > depth[v])swap(u, v);
result = max(result, segTree.query(pos[u] + isEdge, pos[v]));
return result;
}
void updateVertexPath(int u, int v, T value){updatePath(u, v, value, false);}
T queryVertexPath(int u, int v){return queryPath(u, v, false);}
void updateEdgePath(int u, int v, T value){updatePath(u, v, value, true);}
T queryEdgePath(int u, int v){return queryPath(u, v, true);}
void updateSubtree(int u, T value){segTree.update(pos[u], pos[u] + subsize[u] - 1, value);}
T querySubtree(int u){return segTree.query(pos[u], pos[u] + subsize[u] - 1);}
void st(vector<vector<int>> &gr){adj = gr;}
};
