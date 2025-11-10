#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct TNode
{
TNode *child[26];
bool isTerm;
int cnt;
TNode()
{
isTerm = false;
cnt = 0;
for (int i = 0; i < 26; i++)
{
child[i] = nullptr;
}
}
};
struct Trie
{
TNode *root;
Trie()
{
root = new TNode();
}
void insert(const string &s)
{
TNode *rt = root;
for (char ch : s)
{
int idx = ch - 'a';
if (rt->child[idx] == nullptr)
{
rt->child[idx] = new TNode();
}
rt = rt->child[idx];
rt->cnt++;
}
rt->isTerm = true;
}
bool search(const string &s)
{
TNode *rt = root;
for (int i = 0; i < s.size(); i++)
{
int idx = s[i] - 'a';
if (rt->child[idx] == nullptr)
{
return false;
}
rt = rt->child[idx];
}
return rt->isTerm;
}
bool deleteHelper(TNode *rt, const string &s, int pos)
{
if (pos == s.length())
{
if (!rt->isTerm)
{
return false;
}
rt->isTerm = false;
return (rt->cnt == 0);
}
int idx = s[pos] - 'a';
if (rt->child[idx] == nullptr)
{
return false;
}
bool shouldDeleteChild = deleteHelper(rt->child[idx], s, pos + 1);
rt->child[idx]->cnt--;
if (shouldDeleteChild)
{
delete rt->child[idx];
rt->child[idx] = nullptr;
}
return (rt->child[idx] == nullptr) && !rt->isTerm;
}
void remove(const string &s)
{
deleteHelper(root, s, 0);
}
void clear(TNode *rt)
{
if (!rt)
{
return;
}
for (int i = 0; i < 26; i++)
{
clear(rt->child[i]);
}
delete rt;
}
~Trie()
{
clear(root);
}
};
class Trie
{
public:
static const int B = 32; // Number of bits for 32-bit integers
struct Node
{
Node *nxt[2];
int sz; // Number of values passing through this node
Node() : sz(0)
{
nxt[0] = nxt[1] = nullptr;
}
};
Node *root;
Trie()
{
root = new Node();
}
// Insert a number into the Trie
void insert(int val)
{
Node *cur = root;
cur->sz++;
for (int i = B - 1; i >= 0; --i)
{
int bit = (val >> i) & 1;
if (!cur->nxt[bit])
cur->nxt[bit] = new Node();
cur = cur->nxt[bit];
cur->sz++;
}
}
// Query: count numbers 'val' in the Trie such that (val XOR x) < k.
int query(int x, int k)
{
Node *cur = root;
int count = 0;
for (int i = B - 1; i >= 0; --i)
{
if (!cur)
break;
int xBit = (x >> i) & 1;
int kBit = (k >> i) & 1;
if (kBit == 1)
{
// If kth bit is 1, then add all numbers with bit equal to xBit.
if (cur->nxt[xBit])
count += cur->nxt[xBit]->sz;
cur = cur->nxt[1 - xBit]; // move to the branch that differs from xBit
}
else
{
// If kth bit is 0, we must continue in the branch with bit == xBit.
cur = cur->nxt[xBit];
}
}
return count;
}
// Given x, return the maximum XOR achievable with any inserted number.
int getMaxXor(int x)
{
Node *cur = root;
int result = 0;
for (int i = B - 1; i >= 0; --i)
{
int xBit = (x >> i) & 1;
int desired = 1 - xBit; // choose opposite bit if possible
if (cur->nxt[desired])
{
result |= (1 << i);
cur = cur->nxt[desired];
}
else
{
cur = cur->nxt[xBit];
}
}
return result;
}
// Given x, return the minimum XOR achievable with any inserted number.
int getMinXor(int x)
{
Node *cur = root;
int result = 0;
for (int i = B - 1; i >= 0; --i)
{
int xBit = (x >> i) & 1;
if (cur->nxt[xBit])
{
cur = cur->nxt[xBit];
}
else
{
result |= (1 << i);
cur = cur->nxt[1 - xBit];
}
}
return result;
}
// Recursively clear the Trie nodes
void clear(Node *node)
{
if (!node)
return;
clear(node->nxt[0]);
clear(node->nxt[1]);
delete node;
}
~Trie()
{
clear(root);
}
};
// Function to compute maximum and minimum subarray XOR using prefix XORs.
void computeMinMaxXor()
{
int n;
cout << "Enter number of elements: ";
cin >> n;
if (n <= 0)
{
cout << "Array must have at least one element." << endl;
return;
}
vector<int> arr(n);
cout << "Enter array elements: ";
for (int i = 0; i < n; i++)
{
cin >> arr[i];
}
Trie trie;
int prefixXor = 0;
trie.insert(prefixXor);
int maxXor = INT_MIN;
int minXor = INT_MAX;
for (int i = 0; i < n; i++)
{
prefixXor ^= arr[i];
maxXor = max(maxXor, trie.getMaxXor(prefixXor));
minXor = min(minXor, trie.getMinXor(prefixXor));
trie.insert(prefixXor);
}
cout << "Maximum Subarray XOR: " << maxXor << endl;
cout << "Minimum Subarray XOR: " << minXor << endl;
}
// Function to count subarrays with XOR less than a given value k.
void countSubarraysWithXorLessThanK()
{
int n, k;
cout << "Enter number of elements and k: ";
cin >> n >> k;
if (n <= 0)
{
cout << "Array must have at least one element." << endl;
return;
}
vector<int> arr(n);
cout << "Enter array elements: ";
for (int i = 0; i < n; i++)
{
cin >> arr[i];
}
Trie trie;
int prefixXor = 0;
trie.insert(prefixXor);
ll countValid = 0;
for (int i = 0; i < n; i++)
{
prefixXor ^= arr[i];
// The query gives the number of previous prefix XORs that, when XORed with the current prefix, are less than k.
countValid += trie.query(prefixXor, k);
trie.insert(prefixXor);
}
cout << "Count of subarrays with XOR less than " << k << " is " << countValid << endl;
}