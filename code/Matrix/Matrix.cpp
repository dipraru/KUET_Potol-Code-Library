#include<bits/stdc++.h>
using namespace std;
//must 0 based
template<typename T = double>
struct Matrix {
    int n, m;
    vector<vector<T>> a;
    Matrix(): n(0), m(0) {}
    Matrix(int n_, int m_, T init = T()): n(n_), m(m_), a(n_, vector<T>(m_, init)) {}
    vector<T>& operator[](int i){ return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }
    static Matrix Identity(int k) {
        Matrix I(k,k,T());
        for(int i=0;i<k;i++) I.a[i][i] = T(1);
        return I;
    }
    Matrix operator+(Matrix& o){
        assert(n==o.n && m==o.m);
        Matrix r(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) r.a[i][j] = a[i][j] + o.a[i][j];
        return r;
    }
    Matrix operator-(Matrix& o){
        assert(n==o.n && m==o.m);
        Matrix r(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) r.a[i][j] = a[i][j] - o.a[i][j];
        return r;
    }
    Matrix operator*(Matrix& o){
        assert(m == o.n);
        Matrix r(n, o.m, T());
        for(int i=0;i<n;i++){
            for(int k=0;k<m;k++){
                T aik = a[i][k];
                for(int j=0;j<o.m;j++){
                    r.a[i][j] += aik * o.a[k][j];
                }
            }
        }
        return r;
    }
    Matrix pow(long long e){
        assert(n==m);
        if (e == 0) return Identity(n);
        if (e < 0) return inverse().pow(-e);
        Matrix base = *this, res = Identity(n);
        while(e){
            if (e & 1) res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }
    long double determinant(double eps = 1e-12) const {
        assert(n==m);
        int N = n;
        vector<vector<long double>> b(N, vector<long double>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) b[i][j]=a[i][j];
        long double det = 1.0L;
        for (int col = 0; col < N; ++col) {
            int pivot = col;
            for (int i = col + 1; i < N; ++i) if (fabsl(b[i][col]) > fabsl(b[pivot][col])) pivot = i;
            if (fabsl(b[pivot][col]) < eps) return 0; // singular
            if (pivot != col) {
                swap(b[pivot], b[col]);
                det = -det;
            }
            det *= b[col][col];
            long double inv_pivot = 1.0L / b[col][col];
            for (int i = col + 1; i < N; ++i) {
                long double factor = b[i][col] * inv_pivot;
                if (fabsl(factor) < 1e-18L) continue;
                for (int j = col; j < N; ++j)b[i][j] -= factor * b[col][j];
            }
        }
        return det;
    }
    Matrix inverse(double eps = 1e-12){
        if (n != m) throw runtime_error("inverse requires square matrix");
        int N = n;
        vector<vector<double>> aug(N, vector<double>(2*N));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) aug[i][j] = double(a[i][j]);
            for(int j=0;j<N;j++) aug[i][N+j] = (i==j) ? 1.0 : 0.0;
        }
        for(int col=0; col<N; ++col){
            int pivot = col;
            for(int i=col+1;i<N;i++) if (fabs(aug[i][col]) > fabs(aug[pivot][col])) pivot = i;
            if (fabs(aug[pivot][col]) < eps) throw runtime_error("singular matrix (or near-singular)");
            swap(aug[col], aug[pivot]);
            double div = aug[col][col];
            for(int j=0;j<2*N;j++) aug[col][j] /= div;
            for(int i=0;i<N;i++){
                if (i==col) continue;
                double factor = aug[i][col];
                if (fabs(factor) < 1e-18) continue;
                for(int j=col;j<2*N;j++) aug[i][j] -= factor * aug[col][j];
            }
        }
        Matrix res(N,N);
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) res.a[i][j] = T(aug[i][N+j]);
        return res;
    }
    void print(int precision = 10) {
        ios::fmtflags f = cout.flags();
        cout.setf(ios::fixed); cout<<setprecision(precision);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if (j) cout<<' ';
                cout<<a[i][j];
            }
            cout<<"\n";
        }
        cout.flags(f);
    }
};
int main()
{
    int n,m;
    cin >> n >> m;
    Matrix mat(n,m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) cin >> mat[i][j];
    mat.print();
}