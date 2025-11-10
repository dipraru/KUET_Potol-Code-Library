#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
// Ford-Fulkerson Implementation
struct FordFulkerson
{
vector<vector<int>> capacity, adj;
vector<bool> visited;
int n;
FordFulkerson(int n) : n(n)
{
capacity.assign(n + 1, vector<int>(n + 1, 0));
adj.resize(n + 1);
}
void add_edge(int u, int v, int cap)
{
capacity[u][v] += cap;
adj[u].push_back(v);
adj[v].push_back(u); // Reverse edge for residual graph
}
int dfs(int u, int t, int flow)
{
if (u == t)
return flow;
visited[u] = true;
for (int v : adj[u])
{
if (!visited[v] && capacity[u][v] > 0)
{
int bottleneck = dfs(v, t, min(flow, capacity[u][v]));
if (bottleneck > 0)
{
capacity[u][v] -= bottleneck;
capacity[v][u] += bottleneck;
return bottleneck;
}
}
}
return 0;
}
int max_flow(int s, int t)
{
int flow = 0, new_flow;
do
{
visited.assign(n + 1, false);
new_flow = dfs(s, t, INF);
flow += new_flow;
} while (new_flow > 0);
return flow;
}
};
// Edmonds-Karp Implementation
struct EdmondsKarp
{
vector<vector<int>> capacity, adj;
int n;
EdmondsKarp(int n) : n(n)
{
capacity.assign(n + 1, vector<int>(n + 1, 0));
adj.resize(n + 1);
}
void add_edge(int u, int v, int cap)
{
capacity[u][v] += cap;
adj[u].push_back(v);
adj[v].push_back(u); // Reverse edge
}
int bfs(int s, int t, vector<int> &parent)
{
fill(parent.begin(), parent.end(), -1);
parent[s] = -2;
queue<pair<int, int>> q;
q.push({s, INF});
while (!q.empty())
{
auto [u, flow] = q.front();
q.pop();
for (int v : adj[u])
{
if (parent[v] == -1 && capacity[u][v] > 0)
{
parent[v] = u;
int new_flow = min(flow, capacity[u][v]);
if (v == t)
return new_flow;
q.push({v, new_flow});
}
}
}
return 0;
}
int max_flow(int s, int t)
{
int flow = 0, new_flow;
vector<int> parent(n + 1);
while ((new_flow = bfs(s, t, parent)) > 0)
{
flow += new_flow;
int cur = t;
while (cur != s)
{
int prev = parent[cur];
capacity[prev][cur] -= new_flow;
capacity[cur][prev] += new_flow;
cur = prev;
}
}
return flow;
}
};
// Dinic's Algorithm
struct Dinic
{
vector<vector<int>> adj, capacity;
vector<int> level, ptr;
int n;
Dinic(int n) : n(n)
{
adj.resize(n + 1);
capacity.assign(n + 1, vector<int>(n + 1, 0));
level.resize(n + 1);
ptr.resize(n + 1);
}
void add_edge(int u, int v, int cap)
{
capacity[u][v] += cap;
adj[u].push_back(v);
adj[v].push_back(u);
}
bool bfs(int s, int t)
{
fill(level.begin(), level.end(), -1);
level[s] = 0;
queue<int> q;
q.push(s);
while (!q.empty())
{
int u = q.front();
q.pop();
for (int v : adj[u])
{
if (level[v] == -1 && capacity[u][v] > 0)
{
level[v] = level[u] + 1;
q.push(v);
}
}
}
return level[t] != -1;
}
int dfs(int u, int t, int flow)
{
if (u == t || flow == 0)
return flow;
for (int &i = ptr[u]; i < adj[u].size(); i++)
{
int v = adj[u][i];
if (level[v] == level[u] + 1 && capacity[u][v] > 0)
{
int bottleneck = dfs(v, t, min(flow, capacity[u][v]));
if (bottleneck > 0)
{
capacity[u][v] -= bottleneck;
capacity[v][u] += bottleneck;
return bottleneck;
}
}
}
return 0;
}
int max_flow(int s, int t)
{
int flow = 0;
while (bfs(s, t))
{
fill(ptr.begin(), ptr.end(), 0);
while (int new_flow = dfs(s, t, INF))
{
flow += new_flow;
}
}
return flow;
}
};
struct MinCostMaxFlow
{
struct Edge
{
int v, rev;    // Destination and index of the reverse edge
int cap, cost; // Capacity and cost of the edge
};
vector<vector<Edge>> adj;
int n;
MinCostMaxFlow(int n) : n(n)
{
adj.resize(n + 1); // 1-based indexing
}
void add_edge(int u, int v, int cap, int cost)
{
adj[u].push_back({v, (int)adj[v].size(), cap, cost});
adj[v].push_back({u, (int)adj[u].size() - 1, 0, -cost});
}
bool spfa(int s, int t, vector<int> &parent, vector<int> &edge_index, vector<int> &dist)
{
dist.assign(n + 1, INF);
parent.assign(n + 1, -1);
edge_index.assign(n + 1, -1);
vector<bool> in_queue(n + 1, false);
queue<int> q;
dist[s] = 0;
q.push(s);
in_queue[s] = true;
while (!q.empty())
{
int u = q.front();
q.pop();
in_queue[u] = false;
for (int i = 0; i < adj[u].size(); i++)
{
Edge &e = adj[u][i];
if (e.cap > 0 && dist[u] + e.cost < dist[e.v])
{
dist[e.v] = dist[u] + e.cost;
parent[e.v] = u;
edge_index[e.v] = i;
if (!in_queue[e.v])
{
q.push(e.v);
in_queue[e.v] = true;
}
}
}
}
return dist[t] != INF;
}
pair<int, int> max_flow(int s, int t)
{
int total_flow = 0, total_cost = 0;
vector<int> parent, edge_index, dist;
while (spfa(s, t, parent, edge_index, dist))
{
// Find the bottleneck capacity along the path
int push_flow = INF, cur = t;
while (cur != s)
{
int prev = parent[cur];
Edge &e = adj[prev][edge_index[cur]];
push_flow = min(push_flow, e.cap);
cur = prev;
}
// Update the residual graph along the path
cur = t;
while (cur != s)
{
int prev = parent[cur];
Edge &e = adj[prev][edge_index[cur]];
e.cap -= push_flow;
adj[e.v][e.rev].cap += push_flow;
cur = prev;
}
total_flow += push_flow;
total_cost += push_flow * dist[t];
}
return {total_flow, total_cost};
}
};
struct MaxFlow
{
struct Edge
{
int v, rev, cap;
};
int n;
vector<vector<Edge>> adj;
MaxFlow(int n) : n(n)
{
adj.resize(n + 1);
}
void add_edge(int u, int v)
{
adj[u].push_back({v, (int)adj[v].size(), 1});
adj[v].push_back({u, (int)adj[u].size() - 1, 0});
}
bool bfs(int s, int t, vector<int> &parent, vector<int> &edge_index)
{
vector<bool> visited(n + 1, false);
queue<int> q;
q.push(s);
visited[s] = true;
while (!q.empty())
{
int u = q.front();
q.pop();
for (int i = 0; i < adj[u].size(); i++)
{
Edge &e = adj[u][i];
if (!visited[e.v] && e.cap > 0)
{
visited[e.v] = true;
parent[e.v] = u;
edge_index[e.v] = i;
if (e.v == t)
return true;
q.push(e.v);
}
}
}
return false;
}
int max_flow(int s, int t)
{
int total_flow = 0;
while (true)
{
vector<int> parent(n + 1, -1), edge_index(n + 1, -1);
if (!bfs(s, t, parent, edge_index))
break;
int push_flow = INT_MAX, cur = t;
while (cur != s)
{
int prev = parent[cur];
Edge &e = adj[prev][edge_index[cur]];
push_flow = min(push_flow, e.cap);
cur = prev;
}
cur = t;
while (cur != s)
{
int prev = parent[cur];
Edge &e = adj[prev][edge_index[cur]];
e.cap -= push_flow;
adj[cur][e.rev].cap += push_flow;
cur = prev;
}
total_flow += push_flow;
}
return total_flow;
}
void dfs(int u, vector<bool> &visited)
{
visited[u] = true;
for (const auto &e : adj[u])
{
if (e.cap > 0 && !visited[e.v])
{
dfs(e.v, visited);
}
}
}
vector<pair<int, int>> find_min_cut(int s)
{
vector<bool> visited(n + 1, false);
dfs(s, visited);
vector<pair<int, int>> cut_edges;
for (int u = 1; u <= n; u++)
{
if (visited[u])
{
for (const auto &e : adj[u])
{
if (!visited[e.v] && e.cap == 0)
{
cut_edges.emplace_back(u, e.v);
}
}
}
}
return cut_edges;
}
};
struct MaxFlowpath
{
struct Edge
{
int v, rev, cap, flow;
};
int n;
vector<vector<Edge>> adj;
MaxFlowpath(int n) : n(n)
{
adj.resize(n + 1);
}
void add_edge(int u, int v)
{
adj[u].push_back({v, (int)adj[v].size(), 1, 0});
adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
}
bool bfs(int s, int t, vector<int> &parent, vector<int> &edge_index)
{
vector<bool> visited(n + 1, false);
queue<int> q;
q.push(s);
visited[s] = true;
while (!q.empty())
{
int u = q.front();
q.pop();
for (int i = 0; i < adj[u].size(); i++)
{
Edge &e = adj[u][i];
if (!visited[e.v] && e.cap > 0)
{
visited[e.v] = true;
parent[e.v] = u;
edge_index[e.v] = i;
if (e.v == t)
return true;
q.push(e.v);
}
}
}
return false;
}
int max_flow(int s, int t)
{
int total_flow = 0;
while (true)
{
vector<int> parent(n + 1, -1), edge_index(n + 1, -1);
if (!bfs(s, t, parent, edge_index))
break;
int push_flow = INT_MAX, cur = t;
while (cur != s)
{
int prev = parent[cur];
Edge &e = adj[prev][edge_index[cur]];
push_flow = min(push_flow, e.cap);
cur = prev;
}
cur = t;
while (cur != s)
{
int prev = parent[cur];
Edge &e = adj[prev][edge_index[cur]];
e.cap -= push_flow;
e.flow += push_flow;
adj[cur][e.rev].cap += push_flow;
adj[cur][e.rev].flow -= push_flow;
cur = prev;
}
total_flow += push_flow;
}
return total_flow;
}
void dfs(int u, vector<int> &p)
{
p.push_back(u);
for (auto &e : adj[u])
{
if (e.flow > 0)
{
e.flow--;
dfs(e.v, p);
break;
}
}
}
vector<vector<int>> find_disjoint_paths(int s, int f)
{
vector<vector<int>> paths;
while (f--)
{
vector<int> path;
dfs(s, path);
paths.push_back(path);
}
return paths;
}
};
class HopcroftKarp
{
public:
int n, m;
vector<vector<int>> adj;
vector<int> pairU, pairV, dist;
HopcroftKarp(int n, int m) : n(n), m(m)
{
adj.resize(n + 1);
pairU.assign(n + 1, 0);
pairV.assign(m + 1, 0);
dist.assign(n + 1, 0);
}
void addEdge(int u, int v)
{
adj[u].push_back(v);
}
bool bfs()
{
queue<int> q;
for (int u = 1; u <= n; ++u)
{
if (pairU[u] == 0)
{
dist[u] = 0;
q.push(u);
}
else
{
dist[u] = INT_MAX;
}
}
dist[0] = INT_MAX;
while (!q.empty())
{
int u = q.front();
q.pop();
if (dist[u] < dist[0])
{
for (int v : adj[u])
{
if (dist[pairV[v]] == INT_MAX)
{
dist[pairV[v]] = dist[u] + 1;
q.push(pairV[v]);
}
}
}
}
return dist[0] != INT_MAX;
}
bool dfs(int u)
{
if (u != 0)
{
for (int v : adj[u])
{
if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))
{
pairV[v] = u;
pairU[u] = v;
return true;
}
}
dist[u] = INT_MAX;
return false;
}
return true;
}
int maxMatching()
{
int matching = 0;
while (bfs())
{
for (int u = 1; u <= n; ++u)
{
if (pairU[u] == 0 && dfs(u))
{
matching++;
}
}
}
return matching;
}
};
void solve()
{
int n, m, e;
cin >> n >> m >> e; // n: left partition, m: right partition, e: edges
HopcroftKarp hk(n, m);
for (int i = 0; i < e; ++i)
{
int u, v;
cin >> u >> v; // u in left partition (1 to n), v in right partition (1 to m)
hk.addEdge(u, v);
}
cout << hk.maxMatching() << '\n';
}
int main()
{
int n, m;
cin >> n >> m;
FordFulkerson ff(n);
EdmondsKarp ek(n);
Dinic dinic(n);
MinCostMaxFlow mcmf(n);
for (int i = 0; i < m; i++)
{
int u, v, cap, cost;
cin >> u >> v >> cap >> cost;
ff.add_edge(u, v, cap);
ek.add_edge(u, v, cap);
dinic.add_edge(u, v, cap);
mcmf.add_edge(u, v, cap, cost);
}
int s = 1, t = n;
cout << "Ford-Fulkerson Max Flow: " << ff.max_flow(s, t) << "\n";
cout << "Edmonds-Karp Max Flow: " << ek.max_flow(s, t) << "\n";
cout << "Dinic's Max Flow: " << dinic.max_flow(s, t) << "\n";
auto mcmf_result = mcmf.max_flow(s, t);
cout << "Min-Cost Max Flow: Flow = " << mcmf_result.first << ", Cost = " << mcmf_result.second << "\n";
return 0;
}
