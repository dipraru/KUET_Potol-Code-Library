#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SuffixAutomaton
{
    struct State
    {
        int next[26];
        int link;
        int len;
        ll endpos_count;
        State()
        {
            memset(next, -1, sizeof(next));
            link = -1;
            len = 0;
            endpos_count = 0;
        }
    };
    vector<State> st;
    int last; // index of state representing whole string

    SuffixAutomaton(int max_len = 0)
    {
        // Reserve capacity for up to 2 * max_len states to avoid reallocations
        if (max_len > 0)
            st.reserve(2 * max_len);
        // initial state
        st.push_back(State());
        st[0].len = 0;
        st[0].link = -1;
        last = 0;
    }

    // Extend SAM with character ch ('a'..'z')
    void extend(char ch)
    {
        int c = ch - 'a';
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].endpos_count = 1; // each new state corresponds to one new end position
        int p = last;
        // Propagate transitions for character c
        while (p != -1 && st[p].next[c] == -1)
        {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1)
        {
            // No further suffix: link to root
            st[cur].link = 0;
        }
        else
        {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
            {
                // Directly link
                st[cur].link = q;
            }
            else
            {
                // Need to split state q
                int clone = (int)st.size();
                st.push_back(st[q]); // copy q
                st[clone].len = st[p].len + 1;
                st[clone].endpos_count = 0; // clone does not add new endpos immediately
                // Redirect transitions pointing to q to point to clone
                while (p != -1 && st[p].next[c] == q)
                {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // After extending all characters, call this to compute endpos_count for each state
    void compute_endpos_counts()
    {
        int sz = (int)st.size();
        // Bucket states by length
        int max_len = 0;
        for (auto &state : st)
        {
            max_len = max(max_len, state.len);
        }
        vector<int> bucket(max_len + 1, 0);
        for (auto &state : st)
        {
            bucket[state.len]++;
        }
        for (int i = 1; i <= max_len; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        vector<int> order(sz);
        // Sort states by length ascending
        for (int i = sz - 1; i >= 0; i--)
        {
            int l = st[i].len;
            bucket[l]--;
            order[bucket[l]] = i;
        }
        // Propagate counts in descending length order
        for (int idx = sz - 1; idx > 0; idx--)
        {
            int v = order[idx];
            int p = st[v].link;
            if (p != -1)
            {
                st[p].endpos_count += st[v].endpos_count;
            }
        }
        // Now st[v].endpos_count = number of end positions (occurrences) of all substrings represented by v
    }

    // Count distinct substrings: sum_{states v} (len[v] - len[link[v]])
    ll count_distinct_substrings() const
    {
        ll res = 0;
        for (int v = 1; v < (int)st.size(); v++)
        {
            res += (ll)(st[v].len - st[st[v].link].len);
        }
        return res;
    }

    // Check if t is substring of the original string
    bool is_substring(const string &t) const
    {
        int v = 0;
        for (char ch : t)
        {
            int c = ch - 'a';
            if (st[v].next[c] == -1)
                return false;
            v = st[v].next[c];
        }
        return true;
    }

    // Longest common substring between original string and t
    // Returns pair(length, ending position in original string minus 1)
    pair<int, int> longest_common_substring(const string &t) const
    {
        int v = 0, l = 0;
        int best_len = 0, best_pos = -1;
        for (int i = 0; i < (int)t.size(); i++)
        {
            int c = t[i] - 'a';
            if (c < 0 || c >= 26)
            {
                // invalid char, reset
                v = 0;
                l = 0;
                continue;
            }
            if (st[v].next[c] != -1)
            {
                v = st[v].next[c];
                l++;
            }
            else
            {
                // follow suffix links until we can transition or reach root
                while (v != -1 && st[v].next[c] == -1)
                {
                    v = st[v].link;
                }
                if (v == -1)
                {
                    v = 0;
                    l = 0;
                }
                else
                {
                    l = st[v].len + 1;
                    v = st[v].next[c];
                }
            }
            if (l > best_len)
            {
                best_len = l;
                best_pos = i; // ending at i in t; but if we want position in original string, we need more info
            }
        }
        // Note: This finds LCS length and ending pos in t; to get substring in original, one would need endpos info / track positions
        return {best_len, best_pos};
    }

    // For the “k-th substring with duplicates” problem, we need DP f[v] = sum of endpos_count over all reachable states
    vector<ll> f;
    ll dfs_f(int v)
    {
        if (f[v] != -1)
            return f[v];
        ll res = st[v].endpos_count;
        for (int c = 0; c < 26; c++)
        {
            int u = st[v].next[c];
            if (u != -1)
            {
                res += dfs_f(u);
            }
        }
        return f[v] = res;
    }
    // Find k-th substring in lex order including duplicates
    string kth_substring_with_duplicates(ll k)
    {
        int sz = (int)st.size();
        f.assign(sz, -1LL);
        dfs_f(0);
        string ans;
        int v = 0;
        while (k > 0)
        {
            for (int c = 0; c < 26; c++)
            {
                int u = st[v].next[c];
                if (u == -1)
                    continue;
                ll subtree = f[u];
                if (k > subtree)
                {
                    k -= subtree;
                }
                else
                {
                    // pick this character
                    ans.push_back(char('a' + c));
                    ll cnt_here = st[u].endpos_count;
                    if (k <= cnt_here)
                    {
                        return ans;
                    }
                    else
                    {
                        k -= cnt_here;
                        v = u;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
