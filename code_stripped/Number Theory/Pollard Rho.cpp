#include<bits/stdc++.h>
using namespace std;
// ---- gcd ----
uint64_t gcd_stein_impl( uint64_t x, uint64_t y ) {
if( x == y ) { return x; }
const uint64_t a = y - x;
const uint64_t b = x - y;
const int n = __builtin_ctzll( b );
const uint64_t s = x < y ? a : b;
const uint64_t t = x < y ? x : y;
return gcd_stein_impl( s >> n, t );
}
uint64_t gcd_stein( uint64_t x, uint64_t y ) {
if( x == 0 ) { return y; }
if( y == 0 ) { return x; }
const int n = __builtin_ctzll( x );
const int m = __builtin_ctzll( y );
return gcd_stein_impl( x >> n, y >> m ) << ( n < m ? n : m );
}
// ---- is_prime ----
uint64_t mod_pow( uint64_t x, uint64_t y, uint64_t mod ) {
uint64_t ret = 1;
uint64_t acc = x;
for( ; y; y >>= 1 ) {
if( y & 1 ) {
ret = __uint128_t(ret) * acc % mod;
}
acc = __uint128_t(acc) * acc % mod;
}
return ret;
}
bool miller_rabin( uint64_t n, const std::initializer_list<uint64_t>& as ) {
return std::all_of( as.begin(), as.end(), [n]( uint64_t a ) {
if( n <= a ) { return true; }
int e = __builtin_ctzll( n - 1 );
uint64_t z = mod_pow( a, ( n - 1 ) >> e, n );
if( z == 1 || z == n - 1 ) { return true; }
while( --e ) {
z = __uint128_t(z) * z % n;
if( z == 1 ) { return false; }
if( z == n - 1 ) { return true; }
}
return false;
});
}
bool is_prime( uint64_t n ) {
if( n == 2 ) { return true; }
if( n % 2 == 0 ) { return false; }
if( n < 4759123141 ) { return miller_rabin( n, { 2, 7, 61 } ); }
return miller_rabin( n, { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 } );
}
// ---- Montgomery ----
class Montgomery {
uint64_t mod;
uint64_t R;
public:
Montgomery( uint64_t n ) : mod(n), R(n) {
for( size_t i = 0; i < 5; ++i ) {
R *= 2 - mod * R;
}
}
uint64_t fma( uint64_t a, uint64_t b, uint64_t c ) const {
const __uint128_t d = __uint128_t(a) * b;
const uint64_t    e = c + mod + ( d >> 64 );
const uint64_t    f = uint64_t(d) * R;
const uint64_t    g = ( __uint128_t(f) * mod ) >> 64;
return e - g;
}
uint64_t mul( uint64_t a, uint64_t b ) const {
return fma( a, b, 0 );
}
};
// ---- Pollard's rho algorithm ----
uint64_t pollard_rho( uint64_t n ) {
if( n % 2 == 0 ) { return 2; }
const Montgomery m( n );
constexpr uint64_t C1 = 1;
constexpr uint64_t C2 = 2;
constexpr uint64_t M = 512;
uint64_t Z1 = 1;
uint64_t Z2 = 2;
retry:
uint64_t z1 = Z1;
uint64_t z2 = Z2;
for( size_t k = M; ; k *= 2 ) {
const uint64_t x1 = z1 + n;
const uint64_t x2 = z2 + n;
for( size_t j = 0; j < k; j += M ) {
const uint64_t y1 = z1;
const uint64_t y2 = z2;
uint64_t q1 = 1;
uint64_t q2 = 2;
z1 = m.fma( z1, z1, C1 );
z2 = m.fma( z2, z2, C2 );
for( size_t i = 0; i < M; ++i ) {
const uint64_t t1 = x1 - z1;
const uint64_t t2 = x2 - z2;
z1 = m.fma( z1, z1, C1 );
z2 = m.fma( z2, z2, C2 );
q1 = m.mul( q1, t1 );
q2 = m.mul( q2, t2 );
}
q1 = m.mul( q1, x1 - z1 );
q2 = m.mul( q2, x2 - z2 );
const uint64_t q3 = m.mul( q1, q2 );
const uint64_t g3 = gcd_stein( n, q3 );
if( g3 == 1 ) { continue; }
if( g3 != n ) { return g3; }
const uint64_t g1 = gcd_stein( n, q1 );
const uint64_t g2 = gcd_stein( n, q2 );
const uint64_t C = g1 != 1 ? C1 : C2;
const uint64_t x = g1 != 1 ? x1 : x2;
uint64_t       z = g1 != 1 ? y1 : y2;
uint64_t       g = g1 != 1 ? g1 : g2;
if( g == n ) {
do {
z = m.fma( z, z, C );
g = gcd_stein( n, x - z );
} while( g == 1 );
}
if( g != n ) {
return g;
}
Z1 += 2;
Z2 += 2;
goto retry;
}
}
}
void factorize_impl( uint64_t n, std::vector<uint64_t>& ret ) {
if( n <= 1 ) { return; }
if( is_prime( n ) ) { ret.push_back( n ); return; }
const uint64_t p = pollard_rho( n );
factorize_impl( p, ret );
factorize_impl( n / p, ret );
}
std::vector<uint64_t> factorize( uint64_t n ) {
std::vector<uint64_t> ret;
factorize_impl( n, ret );
std::sort( ret.begin(), ret.end() );
return ret;
}
int32_t main() {
long long n;
cin>>n;
vector<uint64_t> factors=factorize(n);
for(auto it:factors)cout<<it<<" ";
}
