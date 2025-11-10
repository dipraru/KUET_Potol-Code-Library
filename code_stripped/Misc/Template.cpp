#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>using orderedSet = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
//order_of_key(k) - number of element strictly less than k
//find_by_order(k) - k'th element in set.(0 indexed)(iterator)
mt19937 mt(std::chrono::steady_clock::now(). time_since_epoch().count());
//uniform_int_distribution<int> dist(1, 100);
struct custom_hash {
static uint64_t splitmix64(uint64_t x) {
x += 0x9e3779b97f4a7c15;
x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
return x ^ (x >> 31);
}
size_t operator()(uint64_t x) const {
static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
return splitmix64(x + FIXED_RANDOM);
}
};
//pair (a, b) er jonne a * MOD + b
gp_hash_table<int, int, custom_hash> mp;
int main(int argc, char* argv[]) {
ios_base::sync_with_stdio(false);//DON'T CC++
cin.tie(NULL);//DON'T use for interactive
int seed = atoi(argv[1]);
//cout << dist(mt) << '\n';
}
