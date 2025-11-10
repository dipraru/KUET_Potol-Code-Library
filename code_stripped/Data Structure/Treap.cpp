#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// Treap supporting multiset behavior and order-statistics, plus split/merge usage examples:
//  - insert(key)
//  - erase(key)          // removes one occurrence if duplicates exist
//  - find(key)           // returns true if exists
//  - kth(k)              // returns the k-th smallest key (1-based); caller must ensure 1 <= k <= size()
//  - count_less(key)     // number of elements strictly less than key
//  - size()              // total number of elements (counting duplicates)
//  - split_root(key, tL, tR): split this treap into tL (< key) and tR (>= key)
//  - merge_root(other): merge this treap with 'other' (all keys in this < keys in other)
struct Treap
{
struct Node
{
ll key;
int prio;
int sz;  // size of subtree counting duplicates via cnt
int cnt; // count of this key (for multiset). If you want set behavior, keep cnt=1 and skip duplicate increments.
Node *l, *r;
Node(ll _key)
: key(_key),
// Use rand() for priority; for stronger randomness, consider mt19937.
prio((int)(rand() ^ (rand() << 15))),
sz(1),
cnt(1),
l(nullptr), r(nullptr)
{
}
};
using pNode = Node *;
pNode root = nullptr;
Treap()
{
// Seed RNG for priorities; can replace with mt19937 if desired.
srand((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
}
private:
// Update size from children and own count
void upd(pNode t)
{
if (!t)
return;
t->sz = t->cnt + get_sz(t->l) + get_sz(t->r);
}
int get_sz(pNode t) const
{
return t ? t->sz : 0;
}
// Split by key: left subtree has keys < key; right subtree has keys >= key.
void split(pNode t, ll key, pNode &l, pNode &r)
{
if (!t)
{
l = r = nullptr;
}
else if (key <= t->key)
{
// t->key >= key: t goes to r; split left subtree
split(t->l, key, l, t->l);
r = t;
upd(r);
}
else
{
// t->key < key: t goes to l; split right subtree
split(t->r, key, t->r, r);
l = t;
upd(l);
}
}
// Merge two treaps l and r, assuming all keys in l < keys in r.
pNode merge(pNode l, pNode r)
{
if (!l || !r)
return l ? l : r;
if (l->prio > r->prio)
{
l->r = merge(l->r, r);
upd(l);
return l;
}
else
{
r->l = merge(l, r->l);
upd(r);
return r;
}
}
// Internal insert: adds key to treap t, returns new root
pNode insert_node(pNode t, ll key)
{
if (!t)
{
return new Node(key);
}
if (t->key == key)
{
// duplicate: increment count
t->cnt++;
}
else if (key < t->key)
{
t->l = insert_node(t->l, key);
if (t->l->prio > t->prio)
{
t = rotate_right(t);
}
}
else
{
t->r = insert_node(t->r, key);
if (t->r->prio > t->prio)
{
t = rotate_left(t);
}
}
upd(t);
return t;
}
// Internal erase: removes one occurrence of key from treap t, returns new root
pNode erase_node(pNode t, ll key)
{
if (!t)
return nullptr;
if (t->key == key)
{
if (t->cnt > 1)
{
// just decrement count
t->cnt--;
}
else
{
// remove this node: merge children
pNode to_delete = t;
t = merge(t->l, t->r);
delete to_delete;
return t;
}
}
else if (key < t->key)
{
t->l = erase_node(t->l, key);
}
else
{
t->r = erase_node(t->r, key);
}
upd(t);
return t;
}
// Right rotation
pNode rotate_right(pNode t)
{
pNode l = t->l;
t->l = l->r;
l->r = t;
upd(t);
upd(l);
return l;
}
// Left rotation
pNode rotate_left(pNode t)
{
pNode r = t->r;
t->r = r->l;
r->l = t;
upd(t);
upd(r);
return r;
}
// Find if key exists
bool find_node(pNode t, ll key) const
{
if (!t)
return false;
if (t->key == key)
return true;
if (key < t->key)
return find_node(t->l, key);
else
return find_node(t->r, key);
}
// Find k-th smallest (1-based). Assumes 1 <= k <= size(t).
ll kth_node(pNode t, int k) const
{
int lsz = get_sz(t->l);
if (k <= lsz)
{
return kth_node(t->l, k);
}
if (k <= lsz + t->cnt)
{
return t->key;
}
return kth_node(t->r, k - lsz - t->cnt);
}
// Count number of elements < key
int count_less_node(pNode t, ll key) const
{
if (!t)
return 0;
if (key <= t->key)
{
return count_less_node(t->l, key);
}
else
{
return get_sz(t->l) + t->cnt + count_less_node(t->r, key);
}
}
public:
// Insert key
void insert(ll key)
{
root = insert_node(root, key);
}
// Erase one occurrence of key (if exists)
void erase(ll key)
{
root = erase_node(root, key);
}
// Check existence
bool find(ll key) const
{
return find_node(root, key);
}
// Get total size (counting duplicates)
int size() const
{
return get_sz(root);
}
// Get k-th smallest (1-based). Caller must ensure 1 <= k <= size().
ll kth(int k) const
{
return kth_node(root, k);
}
// Number of elements strictly less than key
int count_less(ll key) const
{
return count_less_node(root, key);
}
// Split this treap into tL (< key) and tR (>= key).
// After calling, this->root still points to the original root but its pointers have been rearranged.
// Typically you immediately move the results into separate Treap objects.
void split_root(ll key, Treap &tL, Treap &tR)
{
pNode L = nullptr, R = nullptr;
split(root, key, L, R);
tL.root = L;
tR.root = R;
}
// Merge this treap with other, assuming all keys in this < keys in other.
// After merge, other.root becomes nullptr.
void merge_root(Treap &other)
{
root = merge(root, other.root);
other.root = nullptr;
}
// In-order traversal (for debugging): print all keys in ascending order, duplicates repeated.
void inorder_print(pNode t) const
{
if (!t)
return;
inorder_print(t->l);
for (int i = 0; i < t->cnt; i++)
{
cout << t->key << ' ';
}
inorder_print(t->r);
}
void print_inorder() const
{
inorder_print(root);
cout << "\n";
}
};
// Helper: find maximum key in a treap (returns LLONG_MIN if empty)
ll find_max(typename Treap::pNode t)
{
if (!t)
return LLONG_MIN;
while (t->r)
t = t->r;
return t->key;
}
// Helper: find minimum key in a treap (returns LLONG_MAX if empty)
ll find_min(typename Treap::pNode t)
{
if (!t)
return LLONG_MAX;
while (t->l)
t = t->l;
return t->key;
}
// Sample main demonstrating split usage with robust input and no overflow issues.
// Commands (read until EOF):
// 1 x       : insert x
// 2 x       : erase one occurrence of x
// 3 x       : find x, print "YES" or "NO"
// 4 k       : print k-th smallest element, or "INVALID" if k is out of bounds
// 5 x       : print count of elements < x
// 6         : print all elements in sorted order
// 7         : print current size (total elements)
// 8 L R     : delete all keys in [L, R] (inclusive), handling overflow if R = LLONG_MAX
// 9 x       : predecessor of x (largest key < x), print value or "NONE"
// 10 x      : successor strictly > x (smallest key > x), print value or "NONE"
// 11 x      : successor >= x (smallest key >= x), print value or "NONE"
// 12 L R    : count number of elements in [L, R] (inclusive), handling overflow if R = LLONG_MAX
// Any invalid or malformed lines are skipped gracefully.
int main()
{
ios::sync_with_stdio(false);
cin.tie(nullptr);
Treap tr;
int type;
while ((cin >> type))
{
if (type == 1)
{
ll x;
if (!(cin >> x))
break;
tr.insert(x);
}
else if (type == 2)
{
ll x;
if (!(cin >> x))
break;
tr.erase(x);
}
else if (type == 3)
{
ll x;
if (!(cin >> x))
break;
bool ok = tr.find(x);
cout << (ok ? "YES\n" : "NO\n");
}
else if (type == 4)
{
ll k;
if (!(cin >> k))
break;
int n = tr.size();
if (k >= 1 && k <= n)
{
cout << tr.kth((int)k) << "\n";
}
else
{
cout << "INVALID\n";
}
}
else if (type == 5)
{
ll x;
if (!(cin >> x))
break;
cout << tr.count_less(x) << "\n";
}
else if (type == 6)
{
tr.print_inorder();
}
else if (type == 7)
{
cout << tr.size() << "\n";
}
else if (type == 8)
{
ll L, R;
if (!(cin >> L >> R))
break;
if (L > R)
swap(L, R);
// Delete all keys in [L, R], handling overflow
Treap t1, t2, t3;
tr.split_root(L, t1, t2);
if (R == LLONG_MAX)
{
// All keys >= L go into t2; discard t2 entirely
// t3 remains empty
// Merge t1 and empty t3
tr = std::move(t1);
}
else
{
t2.split_root(R + 1, t2, t3); // safe since R < LLONG_MAX
// Discard t2
t1.merge_root(t3);
tr = std::move(t1);
}
}
else if (type == 9)
{
ll x;
if (!(cin >> x))
break;
// Predecessor: largest key < x
Treap tL, tR;
tr.split_root(x, tL, tR);
ll pred = find_max(tL.root);
if (pred == LLONG_MIN)
{
cout << "NONE\n";
}
else
{
cout << pred << "\n";
}
// Merge back
tL.merge_root(tR);
tr = std::move(tL);
}
else if (type == 10)
{
ll x;
if (!(cin >> x))
break;
// Successor strictly > x: smallest key > x
if (x == LLONG_MAX)
{
cout << "NONE\n";
}
else
{
Treap tL, tR;
tr.split_root(x + 1, tL, tR); // safe since x < LLONG_MAX
ll succ = find_min(tR.root);
if (succ == LLONG_MAX)
{
cout << "NONE\n";
}
else
{
cout << succ << "\n";
}
// Merge back
tL.merge_root(tR);
tr = std::move(tL);
}
}
else if (type == 11)
{
ll x;
if (!(cin >> x))
break;
// Successor >= x: smallest key >= x
Treap tL, tR;
tr.split_root(x, tL, tR);
ll succ = find_min(tR.root);
if (succ == LLONG_MAX)
{
cout << "NONE\n";
}
else
{
cout << succ << "\n";
}
// Merge back
tL.merge_root(tR);
tr = std::move(tL);
}
else if (type == 12)
{
ll L, R;
if (!(cin >> L >> R))
break;
if (L > R)
swap(L, R);
// Count elements in [L, R], handling overflow
ll cnt = 0;
if (R == LLONG_MAX)
{
// count of >= L = total size - count_less(L)
cnt = (ll)tr.size() - tr.count_less(L);
}
else
{
cnt = (ll)(tr.count_less(R + 1) - tr.count_less(L)); // safe since R < LLONG_MAX
}
cout << cnt << "\n";
}
else
{
// Unknown command: skip rest of line to avoid input issues
string line;
getline(cin, line);
// Optionally, print an error or ignore
// cout << "UNKNOWN_COMMAND\n";
}
}
return 0;
}
