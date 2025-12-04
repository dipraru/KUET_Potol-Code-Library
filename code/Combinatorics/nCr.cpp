const int MOD=1e9+7;
const int N=4e5+2;
int fact[N], ifact[N], reciprocal[N];
 
struct combinit {
  combinit() {
    reciprocal[1] = 1;
    for (int i = 2; i < N; ++i) {
      reciprocal[i] = (MOD - MOD / i) * (long long)reciprocal[MOD % i] % MOD;
    }
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < N; ++i) {
      fact[i] = (long long)fact[i - 1] * i % MOD;
      ifact[i] = (long long)ifact[i - 1] * reciprocal[i] % MOD;
    }
  }
} combinitX;

long long comb(long long n, long long m) {
  if (n < m || m < 0) return 0;
  return (long long)fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
}