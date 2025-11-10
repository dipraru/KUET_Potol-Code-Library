#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> find_cofactor(vector<vector<int>>
a, int r, int c)
{ vector<vector<int>> mat;
int n = a.size();
for (int i = 0; i < n; i++) {
vector<int> row;
if (r == i) continue;
for (int j = 0; j < n; j++) {
if (j == c) continue;
row.push_back(a[i][j]);
}
mat.push_back(row);
}
return mat;
}
int determinant(vector<vector<int>> a)
{ if (a.size() == 1) {
return a[0][0];
}
int n = a.size();
int sign = +1;
int det = 0;
for (int i = 0; i < n; i++) {
vector<vector<int>> cf_mat = find_cofactor(a,
0, i);
int cofactor = determinant(cf_mat);
det += cofactor * sign * a[0][i];
sign = -sign;
}
return det;
}
vector<vector<int>> transpose(vector<vector<int>> a)
{ int n = a.size();
vector<vector<int>> res(n, vector<int>(n));
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
res[i][j] = a[j][i];
}
}
return res;
}
vector<vector<double>> find_inverse(vector<vector<int>>
a)
{ int n = a.size();
int det = determinant(a);
if (det == 0) {
cout << "Inverse Impossible\n";
return {{}};
}
vector<vector<int>> cofactor_matrix(n,
vector<int>(n));
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
int sign = (i + j)%2 ? -1 : +1;
cofactor_matrix[i][j] = sign *
determinant(find_cofactor(a, i, j));
}
}
auto adj_matrix = transpose(cofactor_matrix);
auto inverse_mat = vector<vector<double>>(n,
vector<double>(n));
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
inverse_mat[i][j] = 1.0 * adj_matrix[i][j] /
det;
}
}
return inverse_mat;
}
signed main()
{ vector<vector<int>> mat = {
{2, -3, 1},
{2, 0, -1},
{1, 4, 5}
};
int det = determinant(mat);
cout << det << "\n";
auto inverse = find_inverse(mat);
int n = inverse.size();
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
cout << inverse[i][j] << " \n"[j + 1 == n];
}
}
}
