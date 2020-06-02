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

const int N = 61;
const int NN = 1000001;
const int IMAX = 1e9+7;

ll T, dp[N][N]; string s;

ll solve (int l, int r) {
    if (l == r)
        return 1; // A
    if (l+1 == r)
        return 2 + (s[l] == s[r] ? 1 : 0); // AA or AB; {AAA,A,A} vs {A,B} 

    ll& ans = dp[l][r];
    if (ans != -1)
        return ans;

    ans = 0;
    if (s[l] == s[r])
        ans += solve(l+1,r-1)+1;
    ans += solve(l+1,r);
    ans += solve(l,r-1);
    ans -= solve(l+1,r-1); // double counted
    return ans;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> T;
    while (T--) {
        memset(dp, -1, sizeof dp);
        cin >> s;
        cout << solve(0,s.size()-1) << endl;
    }
    return 0;
}