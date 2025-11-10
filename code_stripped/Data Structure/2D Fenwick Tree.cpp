struct FenwickTree2D
{
vector<vector<int>> tree;
int n;
void init(int size){n = size,tree.assign(n + 1, vector<int>(n + 1, 0));}
void update(int x, int y, int delta)
{
for (int i = x; i <= n; i += (i & -i))
for (int j = y; j <= n; j += (j & -j))tree[i][j] += delta;
}
int query(int x, int y)
{
int sum = 0;
for (int i = x; i > 0; i -= (i & -i))
for (int j = y; j > 0; j -= (j & -j))sum += tree[i][j];
return sum;
}
int query(int x1, int y1, int x2, int y2){return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);}
};