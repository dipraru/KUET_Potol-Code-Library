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
            if (!rt->isTerm) return false;
            rt->isTerm = false;
            return (rt->cnt == 0);
        }
        int idx = s[pos] - 'a';
        if (rt->child[idx] == nullptr) return false;
        bool delch = deleteHelper(rt->child[idx], s, pos + 1);
        rt->child[idx]->cnt--;
        if (delch)
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