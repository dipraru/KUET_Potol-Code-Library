#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct BitMan
{
// Shift right by b bits (zero-based)
long long shiftr(long long x, long long b)
{
return x >> b;
}
// Shift left by b bits (zero-based)
long long shiftl(long long x, long long b)
{
return x << b;
}
// Turn on the b-th bit (zero-based)
long long turnon(long long x, long long b)
{
return x | (1LL << b);
}
// Turn off the b-th bit (zero-based)
long long turnoff(long long x, long long b)
{
return x & ~(1LL << b);
}
// Toggle the b-th bit (zero-based)
long long toggle(long long x, long long b)
{
return x ^ (1LL << b);
}
// Get the lowest active bit
long long lowActive(long long x)
{
return x & (-x);
}
// Turn on all bits from 0 to b-1
long long onall(long long b)
{
return (1LL << b) - 1;
}
// Print all subsets of the bitmask x
void subset(long long x)
{
for (long long i = x; i > 0; i = x & (i - 1))
{
cout << i << endl;
}
}
// Check if the b-th bit is on (zero-based)
bool checkbit(long long x, long long b)
{
return (x & (1LL << b)) != 0;
}
// Count the number of set bits
int cntset(long long x)
{
return __builtin_popcountll(x);
}
// Count the number of trailing zeros
int tailzero(long long x)
{
return __builtin_ctzll(x);
}
// Count the number of leading zeros
int leadzero(long long x)
{
return __builtin_clzll(x);
}
// Get a bitmask with the rightmost n bits set
long long rightmost_bits(int n)
{
return (1LL << n) - 1;
}
// print bit
void bpr(long long x)
{
vector<ll> v(64);
for (int i = 0; i < 63; i++)
{
if (checkbit(x, i))
{
v[i] = 1;
}
}
if (x < 0)
{
v[63] = 1;
}
for (int i = 0; i < 64; i++)
{
cout << "(" << i << " " << v[i] << ") ";
}
cout << endl;
}
// Get the position of the highest set bit (zero-based)
int highest_set_bit(long long x)
{
return 63 - __builtin_clzll(x);
}
// Get the position of the lowest set bit (zero-based)
int lowest_set_bit(long long x)
{
return __builtin_ctzll(x);
}
// Bitwise AND of x and y
long long bitwise_and(long long x, long long y)
{
return x & y;
}
// Bitwise OR of x and y
long long bitwise_or(long long x, long long y)
{
return x | y;
}
// Bitwise XOR of x and y
long long bitwise_xor(long long x, long long y)
{
return x ^ y;
}
// Bitwise NOT of x
long long bitwise_not(long long x)
{
return ~x;
}
// Check if exactly one bit is set
bool has_exactly_one_bit_set(long long x)
{
return x != 0 && (x & (x - 1)) == 0;
}
// Get the number of bits required to represent x
int bit_length(long long x)
{
return 64 - __builtin_clzll(x);
}
};