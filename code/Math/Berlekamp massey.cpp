#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int64 MOD = 1000000007;

int64 modpow(int64 a, int64 e){
    int64 r=1%MOD;
    a%=MOD;
    while(e){
        if(e&1) r = (__int128)r*a % MOD;
        a = (__int128)a*a % MOD;
        e >>= 1;
    }
    return r;
}
int64 modinv(int64 x){ return modpow((x%MOD+MOD)%MOD, MOD-2); }

// --- Fast doubling for Fibonacci (returns pair (F_n, F_{n+1})) ---
pair<int64,int64> fib_pair(long long n){
    if(n==0) return {0,1};
    auto p = fib_pair(n>>1);
    int64 a = p.first, b = p.second;
    int64 c = ( (__int128)a * ( (2*b - a + MOD) % MOD ) ) % MOD; // F(2k)
    int64 d = ( (__int128)a*a + (__int128)b*b ) % MOD;           // F(2k+1)
    if(n&1) return {d, (c+d)%MOD};
    else    return {c,d};
}
int64 fib(long long n){ return fib_pair(n).first; }

// --- Matrix utilities for small matrices (square) ---
using Mat = vector<vector<int64>>;

Mat matMul(const Mat &A, const Mat &B){
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    Mat C(n, vector<int64>(m,0));
    for(int i=0;i<n;i++){
        for(int k=0;k<p;k++){
            if(A[i][k]==0) continue;
            int64 av = A[i][k];
            for(int j=0;j<m;j++){
                C[i][j] = (C[i][j] + av * B[k][j]) % MOD;
            }
        }
    }
    return C;
}
Mat matPow(Mat base, long long e){
    int n = base.size();
    Mat R(n, vector<int64>(n,0));
    for(int i=0;i<n;i++) R[i][i]=1;
    while(e){
        if(e&1) R = matMul(R, base);
        base = matMul(base, base);
        e >>= 1;
    }
    return R;
}

// --- Berlekamp-Massey: returns coefficients c (length L) so that
//     a_n = c[0]*a_{n-1} + c[1]*a_{n-2} + ... + c[L-1]*a_{n-L}
//     (i.e., recurrence of order L). Works modulo MOD. ---
vector<int64> berlekamp_massey(const vector<int64>& s){
    int n = s.size();
    vector<int64> C(1,1), B(1,1);
    int L = 0, m = 1;
    int64 b = 1;
    for(int i=0;i<n;i++){
        // compute discrepancy
        int64 d = 0;
        for(int j=0;j<=L;j++){
            d = (d + C[j] * s[i-j]) % MOD;
        }
        if(d==0){
            m++;
        } else {
            vector<int64> T = C;
            int64 coef = d * modinv(b) % MOD;
            // C = C - coef * x^m * B
            int need = max((int)C.size(), (int)B.size() + m);
            C.resize(need);
            for(size_t j=0;j<B.size();j++){
                int idx = j + m;
                C[idx] = (C[idx] - coef * B[j]) % MOD;
                if(C[idx]<0) C[idx]+=MOD;
            }
            if(2*L <= i){
                L = i+1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                m++;
            }
        }
    }
    // currently C represents polynomial with leading 1 and C[0]=1
    // We want recurrence a_n = sum_{i=1..L} coeff[i-1] * a_{n-i}
    // For that, coeff[i-1] = (MOD - C[i]) % MOD  for i=1..L
    vector<int64> res;
    for(int i=1;i<(int)C.size();i++){
        res.push_back( (MOD - C[i]) % MOD );
    }
    return res;
}

// --- Helper: compute sum_{i=0..N} a_i given recurrence and initial values ---
// recurrence length L, coeffs c[0..L-1], initial a[0..L-1]
int64 sum_linear_recurrence(const vector<int64>& c, const vector<int64>& init, long long N){
    int L = c.size();
    if(N < (int)init.size()){
        int64 s=0;
        for(int i=0;i<=N;i++) s = (s + init[i]) % MOD;
        return s;
    }
    // Build augmented matrix M of size (L+1)x(L+1)
    int sz = L+1;
    Mat M(sz, vector<int64>(sz,0));
    // top row -> next value a_{n+1} = sum c[j]*a_{n-j}
    for(int j=0;j<L;j++) M[0][j] = c[j] % MOD;
    // shift rows
    for(int i=1;i<L;i++){
        M[i][i-1] = 1;
    }
    // last row: S_{n+1} = S_n + a_{n+1} = S_n + dot(c, top L entries)
    for(int j=0;j<L;j++) M[L][j] = c[j] % MOD;
    M[L][L] = 1;
    // initial state vector at index n = L-1:
    // u_{L-1} = [ a_{L-1}, a_{L-2}, ..., a_0, S_{L-1} ]^T
    Mat u(sz, vector<int64>(1,0));
    int64 S_init = 0;
    for(int i=0;i<L;i++) S_init = (S_init + init[i]) % MOD;
    for(int i=0;i<L;i++){
        u[i][0] = init[L-1 - i]; // top element a_{L-1}
    }
    u[L][0] = S_init;
    long long exp = N - (L - 1);
    Mat P = matPow(M, exp);
    Mat res = matMul(P, u);
    int64 ans = res[L][0] % MOD; if(ans<0) ans+=MOD;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    for(int tc=1; tc<=T; ++tc){
        long long N; long long C; int K;
        cin >> N >> C >> K;
        // We need sequence a_n = (F_{n*C})^K for n=0..N
        // Prepare initial terms: need at least 2*(K+1) terms to run BM safely.
        int need = 2*(K+1) + 5; // a bit extra margin
        vector<int64> seq;
        seq.reserve(need);
        for(int i=0;i<need;i++){
            int64 f = fib((long long)i * C); // F_{iC} mod MOD
            int64 val = modpow(f, K);
            seq.push_back(val);
        }
        // Run Berlekamp-Massey on seq to get recurrence
        vector<int64> rec = berlekamp_massey(seq);
        int L = rec.size();
        if(L==0){
            // sequence is all zero -> sum=0
            cout << "Case " << tc << ": 0\n";
            continue;
        }
        // initial a[0..L-1]
        vector<int64> init(L);
        for(int i=0;i<L;i++) init[i] = seq[i] % MOD;
        // Compute sum from 0..N
        int64 ans = sum_linear_recurrence(rec, init, N);
        cout << "Case " << tc << ": " << ans % MOD << "\n";
    }
    return 0;
}
