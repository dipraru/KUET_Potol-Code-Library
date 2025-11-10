#include <bits/stdc++.h>
using namespace std;
struct AhoCorasick
{
struct Node
{
int children[26], go[26], fail;
int patternCount;             // Count patterns ending here
vector<int> patternIndices;   // Stores pattern IDs
Node()
{
memset(children, -1, sizeof(children));
memset(go, -1, sizeof(go));
fail = -1;
patternCount = 0;
}
};
vector<Node> nodes;
int root;
AhoCorasick()
{
root = 0;
nodes.push_back(Node());
}
int charToIndex(char c)
{
return c - 'a';  // assumes lowercase 'a' to 'z'
}
// Insert pattern, assign an ID
void insert(const string &s, int id)
{
int curr = root;
for (char c : s)
{
int i = charToIndex(c);
if (nodes[curr].children[i] == -1)
{
nodes[curr].children[i] = nodes.size();
nodes.push_back(Node());
}
curr = nodes[curr].children[i];
}
nodes[curr].patternCount++;
nodes[curr].patternIndices.push_back(id);
}
void build()
{
queue<int> q;
nodes[root].fail = root;
// Initialize go transitions for root
for (int i = 0; i < 26; ++i)
{
if (nodes[root].children[i] != -1)
{
int child = nodes[root].children[i];
nodes[child].fail = root;
q.push(child);
nodes[root].go[i] = child;
}
else
{
nodes[root].go[i] = root;
}
}
while (!q.empty())
{
int curr = q.front();
q.pop();
for (int i = 0; i < 26; ++i)
{
int child = nodes[curr].children[i];
if (child != -1)
{
int fail = nodes[curr].fail;
while (fail != root && nodes[fail].children[i] == -1)
fail = nodes[fail].fail;
if (nodes[fail].children[i] != -1)
fail = nodes[fail].children[i];
else
fail = root;
nodes[child].fail = fail;
nodes[child].patternCount += nodes[fail].patternCount;
// Merge pattern counts and IDs
for (int id : nodes[fail].patternIndices)
nodes[child].patternIndices.push_back(id);
q.push(child);
nodes[curr].go[i] = child;
}
else
{
nodes[curr].go[i] = nodes[nodes[curr].fail].go[i];
}
}
}
}
// Count total occurrences
int searchCount(const string &text)
{
int curr = root;
int count = 0;
for (char c : text)
{
int i = charToIndex(c);
curr = nodes[curr].go[i];
count += nodes[curr].patternCount;
}
return count;
}
// Get matched pattern ids with position
vector<pair<int, int>> searchWithIndex(const string &text)
{
vector<pair<int, int>> matches;
int curr = root;
for (int j = 0; j < text.size(); ++j)
{
int i = charToIndex(text[j]);
curr = nodes[curr].go[i];
int temp = curr;
while (temp != root)
{
for (int id : nodes[temp].patternIndices)
matches.push_back({id, j});
temp = nodes[temp].fail;
}
}
return matches;
}
};
