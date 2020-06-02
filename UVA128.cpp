#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<int> t; t.insert(...);
// t.find_by_order(index); // 0-based
// t.order_of_key(key); --> STRICTLY LESS THAN KEY

// from: https://codeforces.com/blog/entry/62393
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
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

const int N = 15;
const int NN = 1000001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

const int g = 34943;

string s;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0);
    while (getline(cin, s)) {
        if (s == "#") break;
        int n = s.size();
        unsigned long long m = 0;
        for (int i = 0; i < s.size(); ++i) {
            m <<= 8; 
            m += int(s[i]); // each "bit"
            m %= g; // but it gets mod by g anyway
        }
        m <<= 16; // g is 16 bit, aka 4 letters
        m %= g;

        int crc = (g-m)%g;
        printf("%02X %02X\n", crc >> 8, crc%256); // useful thing!!!
    }

    return 0;
}