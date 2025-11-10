struct SimpleHash {
    long long len, base, mod;
    vector<int> P, H, R;
    SimpleHash() {}
    SimpleHash(string str, long long b, long long m) {
        base = b, mod = m, len = str.size();
        P.resize(len + 4, 1), H.resize(len + 3, 0), R.resize(len + 3, 0);
        for (long long i = 1; i <= len + 3; i++)
            P[i] = ((ll)P[i - 1] * base) % mod;
        for (long long i = 1; i <= len; i++)
            H[i] = ((ll)H[i - 1] * base + str[i - 1]+1007) % mod;
        for (long long i = len; i >= 1; i--)
            R[i] = ((ll)R[i + 1] * base + str[i - 1]+1007) % mod;
    }
    inline long long range_hash(long long l, long long r) {
        long long hashval = ((ll)H[r + 1] - ((ll)P[r - l + 1] * (ll)H[l] % mod))%mod;
        return (hashval < 0 ? hashval + mod : hashval);
    }
    inline long long reverse_hash(long long l, long long r) {
        long long hashval = (ll)R[l + 1] - ((ll)P[r - l + 1] * (ll)R[r + 2] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }
};
struct DoubleHash {
    SimpleHash sh1, sh2;
    DoubleHash() {}
    DoubleHash(string str) {
        sh1 = SimpleHash(str, 1949313259, 2091573227);
        sh2 = SimpleHash(str, 1997293877, 2117566807);
    }
    long long concate(DoubleHash& B, long long l1 , long long r1 , long long l2 , long long r2) {
        long long len1 = r1 - l1+1 , len2 = r2 - l2+1;
        long long x1 = sh1.range_hash(l1, r1) ,
        x2 = B.sh1.range_hash(l2, r2);
        x1 = (x1 * B.sh1.P[len2]) % 2091573227;
        long long newx1 = (x1 + x2) % 2091573227;
        x1 = sh2.range_hash(l1, r1);
        x2 = B.sh2.range_hash(l2, r2);
        x1 = (x1 * B.sh2.P[len2]) % 2117566807;
        long long newx2 = (x1 + x2) % 2117566807;
        return (newx1 << 32) ^ newx2;
    }
    inline long long range_hash(long long l, long long r) {
        return (sh1.range_hash(l, r) << 32) ^ sh2.range_hash(l, r);
    }
    inline long long reverse_hash(long long l, long long r) {
        return (sh1.reverse_hash(l, r) << 32) ^ sh2.reverse_hash(l, r);
    }
};