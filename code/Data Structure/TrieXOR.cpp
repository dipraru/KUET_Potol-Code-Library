#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Trie
{
public:
    static const int B = 32;
    struct Node
    {
        Node *nxt[2];
        int sz;
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
    void insert(int val)
    {
        Node *cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; --i)
        {
            int bit = (val >> i) & 1;
            if (!cur->nxt[bit]) cur->nxt[bit] = new Node();
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
            if (!cur) break;
            int xBit = (x >> i) & 1, kBit = (k >> i) & 1;
            if (kBit == 1)
            {
                if (cur->nxt[xBit]) count += cur->nxt[xBit]->sz;
                cur = cur->nxt[1 - xBit];
            }
            else  cur = cur->nxt[xBit];
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
            int desired = 1 - xBit;
            if (cur->nxt[desired])
            {
                result |= (1 << i);
                cur = cur->nxt[desired];
            }
            else cur = cur->nxt[xBit];
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
            if (cur->nxt[xBit]) cur = cur->nxt[xBit];
            else
            {
                result |= (1 << i);
                cur = cur->nxt[1 - xBit];
            }
        }
        return result;
    }
    void erase(int val)
    {
        Node *cur = root;
        cur->sz--;
        for (int i = B - 1; i >= 0; --i)
        {
            int bit = (val >> i) & 1;
            Node *next = cur->nxt[bit];
            next->sz--;
            if (next->sz == 0)
            {
                clear(next);
                cur->nxt[bit] = nullptr;
                return;
            }
            cur = next;
        }
    }
    void clear(Node *node)
    {
        if (!node) return;
        clear(node->nxt[0]);
        clear(node->nxt[1]);
        delete node;
    }
};