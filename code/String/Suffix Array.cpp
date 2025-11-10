#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SuffixArray
{
    string s;
    int n;
    vector<int> sa, rank_arr,lcp,log2;
    vector<vector<int>> st;
    SuffixArray(const string &str)
    {
        s = str,n = s.size();
        sa.assign(n, 0);
        rank_arr.assign(n, 0);
        build_sa(),build_lcp(),build_rmq();
    }
    void build_sa()
    {
        vector<int> rnk(n), tmp(n), cnt;
        int alphabet = 256;
        cnt.assign(alphabet, 0);
        for (int i = 0; i < n; i++)cnt[(unsigned char)s[i]]++;
        for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            unsigned char c = (unsigned char)s[i];
            cnt[c]--,sa[cnt[c]] = i;
        }
        int classes = 1;
        rnk[sa[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (s[sa[i]] != s[sa[i - 1]])classes++;
            rnk[sa[i]] = classes - 1;
        }
        for (int h = 1; h < n && classes < n; h <<= 1)
        {
            cnt.assign(classes + 1, 0);
            for (int i = 0; i < n; i++)
            {
                int idx = sa[i];
                int key = (idx + h < n ? rnk[idx + h] + 1 : 0);
                cnt[key]++;
            }
            for (int i = 1; i < (int)cnt.size(); i++)cnt[i] += cnt[i - 1];
            vector<int> sa2(n);
            for (int i = n - 1; i >= 0; i--)
            {
                int idx = sa[i];
                int key = (idx + h < n ? rnk[idx + h] + 1 : 0);
                cnt[key]--;
                sa2[cnt[key]] = idx;
            }
            cnt.assign(classes, 0);
            for (int i = 0; i < n; i++) cnt[rnk[sa2[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
            {
                int idx = sa2[i];
                int key = rnk[idx];
                cnt[key]--,sa[cnt[key]] = idx;
            }
            vector<int> rnk2(n);
            rnk2[sa[0]] = 0, classes = 1;
            for (int i = 1; i < n; i++)
            {
                int cur = sa[i], prev = sa[i - 1];
                int mid = (cur + h < n ? rnk[cur + h] : -1);
                int mid_prev = (prev + h < n ? rnk[prev + h] : -1);
                if (rnk[cur] != rnk[prev] || mid != mid_prev) classes++;
                rnk2[cur] = classes - 1;
            }
            rnk = move(rnk2);
        }
        rank_arr = move(rnk);
    }

    void build_lcp()
    {
        lcp.assign(n, 0);
        int h = 0;
        for (int i = 0; i < n; i++)
        {
            int r = rank_arr[i];
            if (r == 0)
            {
                lcp[r] = 0;
                continue;
            }
            int j = sa[r - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[r] = h;
            if (h > 0) h--;
        }
    }
    void build_rmq()
    {
        int m = n;
        log2.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) log2[i] = log2[i / 2] + 1;
        int K = log2[m] + 1;
        st.assign(K, vector<int>(m));
        for (int i = 0; i < m; i++) st[0][i] = lcp[i];
        for (int k = 1; k < K; k++)
        {
            int len = 1 << k;
            int half = 1 << (k - 1);
            for (int i = 0; i + len <= m; i++) st[k][i] = min(st[k - 1][i], st[k - 1][i + half]);
        }
    }
    int get_lcp(int i, int j) const
    {
        if (i == j) return n - i;
        int ri = rank_arr[i], rj = rank_arr[j];
        if (ri > rj) swap(ri, rj);
        int L = ri + 1, R = rj;
        int len = R - L + 1;
        int k = log2[len];
        return min(st[k][L], st[k][R - (1 << k) + 1]);
    }
    ll count_distinct_substrings() const
    {
        ll total = (ll)n * (n + 1) / 2;
        ll sum = 0;
        for (int i = 1; i < n; i++) sum += lcp[i];
        return total - sum;
    }
    string kth_substring(ll k) const
    {
        for (int i = 0; i < n; i++)
        {
            ll suffix_len = n - sa[i];
            ll common = (i > 0 ? (ll)lcp[i] : 0LL);
            ll new_sub = suffix_len - common;
            if (k <= new_sub) return s.substr(sa[i], (size_t)(common + k));
            k -= new_sub;
        }
        return ""; // should not happen if k is valid
    }

    bool substring_search(const string &t) const
    {
        int m = t.size();
        int l = 0, r = n - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            int start = sa[mid];
            int cmp = 0;
            for (int k = 0; k < m; k++)
            {
                if (start + k >= n)
                {
                    cmp = -1;
                    break;
                }
                if (s[start + k] < t[k])
                {
                    cmp = -1;
                    break;
                }
                if (s[start + k] > t[k])
                {
                    cmp = 1;
                    break;
                }
            }
            if (cmp == 0)return true;
            if (cmp < 0) l = mid + 1;
            else r = mid - 1;
        }
        return false;
    }
    int compare_substrings(int l1, int r1, int l2, int r2) const
    {
        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int common = get_lcp(l1, l2);
        if (common >= min(len1, len2))
        {
            if (len1 == len2) return 0;
            return (len1 < len2) ? -1 : 1;
        }
        char c1 = s[l1 + common];
        char c2 = s[l2 + common];
        return (c1 < c2) ? -1 : 1;
    }
    string longest_palindromic_substring() const
    {
        string rs = s;
        reverse(rs.begin(), rs.end());
        string comb = s + '#' + rs;
        SuffixArray sa2(comb);
        int n1 = n;
        int best_len = 0, best_pos = 0;
        for (int i = 0; i < n1; i++)
        {
            int l1 = i, l2 = n1 + 1 + (n1 - 1 - i);
            int common = sa2.get_lcp(l1, l2);
            int len_odd = 2 * common - 1;
            if (common > 0 && len_odd > best_len)
            {
                best_len = len_odd;
                best_pos = i - common + 1;
            }
        }
        for (int i = 1; i < n1; i++)
        {
            int l1 = i;
            int l2 = n1 + 1 + (n1 - i);
            int common = sa2.get_lcp(l1, l2);
            int len_even = 2 * common;
            if (common > 0 && len_even > best_len)
            {
                best_len = len_even;
                best_pos = i - common;
            }
        }
        if (best_len <= 0) return s.substr(0, 1);
        return s.substr(best_pos, best_len);
    }
    pair<int, string> longest_common_substring(const string &t) const
    {
        string comb = s + '#' + t;
        int n1 = n;
        SuffixArray sa2(comb);
        int totalN = comb.size();
        int best_lcp = 0,best_pos = 0;
        for (int i = 1; i < totalN; i++)
        {
            int p = sa2.sa[i - 1];
            int q = sa2.sa[i];
            bool in1 = (p < n1);
            bool in2 = (q > n1);
            if (in1 && in2)
            {
                int cur = sa2.lcp[i];
                if (cur > best_lcp)
                {
                    best_lcp = cur;
                    best_pos = sa2.sa[i];
                }
            }
            else if ((q < n1) && (p > n1))
            {
                int cur = sa2.lcp[i];
                if (cur > best_lcp)
                {
                    best_lcp = cur;
                    best_pos = sa2.sa[i - 1];
                }
            }
        }
        if (best_lcp == 0) return {0, ""};
        return {best_lcp, comb.substr(best_pos, best_lcp)};
    }
};
