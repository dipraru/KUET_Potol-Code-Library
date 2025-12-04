vector<int> pri;
vector<int> lp;   // lowest prime factor
void sieve(int n) {
    lp.assign(n + 1, 0);
    pri.clear();
    for (int i = 2; i <= n; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            pri.push_back(i);
        }
        for (int p : pri) {
            if (p > lp[i] || 1LL * p * i > n) break;
            lp[p * i] = p;
        }
    }
}
