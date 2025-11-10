void build(){for (int i = 1; i <= n; ++i)
for (int j = 1; j <= m; ++j)prefix[i][j] = arr[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];}
int query(int x1, int y1, int x2, int y2){return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];}