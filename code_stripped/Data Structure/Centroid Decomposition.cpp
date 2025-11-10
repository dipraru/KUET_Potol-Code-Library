#include <bits/stdc++.h>
using namespace std;
struct CentroidDecomposition
{
int n;
int INF = INT_MAX;
vector<vector<int>> adj;
vector<bool> centroidMarked;
vector<int> subSize;
vector<int> parentCentroid;
vector<vector<pair<int, int>>> centroidPath;
vector<multiset<int>> bestSet;
CentroidDecomposition(int _n) : n(_n)
{
adj.assign(n + 1, {});
centroidMarked.assign(n + 1, false);
subSize.assign(n + 1, 0);
parentCentroid.assign(n + 1, 0);
centroidPath.assign(n + 1, {});
bestSet.assign(n + 1, {});
}
void addEdge(int u, int v)
{
adj[u].push_back(v);
adj[v].push_back(u);
}
void computeSubSizeDFS(int u, int p)
{
subSize[u] = 1;
for (int v : adj[u])
{
if (v == p || centroidMarked[v])
continue;
computeSubSizeDFS(v, u);
subSize[u] += subSize[v];
}
}
int findCentroidDFS(int u, int p, int totSize)
{
for (int v : adj[u])
{
if (v == p || centroidMarked[v])
continue;
if (subSize[v] > totSize / 2)
{
return findCentroidDFS(v, u, totSize);
}
}
return u;
}
void addCentroidDistances(int c)
{
queue<pair<int, int>> q;
vector<char> visited(n + 1, 0);
q.push({c, 0});
visited[c] = 1;
centroidPath[c].push_back({c, 0});
while (!q.empty())
{
auto [u, d] = q.front();
q.pop();
for (int v : adj[u])
{
if (centroidMarked[v] || visited[v])
continue;
visited[v] = 1;
centroidPath[v].push_back({c, d + 1});
q.push({v, d + 1});
}
}
}
void decompose(int entry, int pCent)
{
computeSubSizeDFS(entry, 0);
int totalSize = subSize[entry];
int c = findCentroidDFS(entry, 0, totalSize);
centroidMarked[c] = true;
parentCentroid[c] = (pCent == 0 ? c : pCent);
addCentroidDistances(c);
for (int v : adj[c])
{
if (!centroidMarked[v])
{
decompose(v, c);
}
}
}
void build()
{
decompose(1, 0);
}
void update(int v)
{
for (auto &pr : centroidPath[v])
{
int c = pr.first;
int d = pr.second;
bestSet[c].insert(d);
}
}
void remove(int v)
{
for (auto &pr : centroidPath[v])
{
int c = pr.first;
int d = pr.second;
auto it = bestSet[c].find(d);
if (it != bestSet[c].end())
{
bestSet[c].erase(it);
}
}
}
int query(int v)
{
int res = INF;
for (auto &pr : centroidPath[v])
{
int c = pr.first;
int d = pr.second;
if (!bestSet[c].empty())
{
res = min(res, d + *bestSet[c].begin());
}
}
return res;
}
};
