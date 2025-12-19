struct SuffixArray
{
    string s;
    int n;
    vector<int> sa, rank_arr, lcp; 
    SuffixArray(const string &str)
    {
        s = str;
        n = s.size();
        sa.assign(n, 0);
        rank_arr.assign(n, 0);
        build_sa();
        build_lcp();
    }
    void build_sa()
    {
        vector<int> rnk(n), tmp(n), cnt;
        int alphabet = 256;
        cnt.assign(alphabet, 0);
        for (int i = 0; i < n; i++)
        {
            unsigned char c = (unsigned char)s[i];
            cnt[c]++;
        }
        for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            unsigned char c = (unsigned char)s[i];
            cnt[c]--;
            sa[cnt[c]] = i;
        }
        int classes = 1;
        rnk[sa[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (s[sa[i]] != s[sa[i - 1]]) classes++;
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
            for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
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
                cnt[key]--;
                sa[cnt[key]] = idx;
            }
            vector<int> rnk2(n);
            rnk2[sa[0]] = 0;
            classes = 1;
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
};