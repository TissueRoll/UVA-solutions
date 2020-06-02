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

const int N = 10001;
const int NN = 1000001;
const int IMAX = 1e9+7;

int T, n, k, v[N];//, dp[5001][5001][21];

int solve (int l, int r, int moves) {
    if (l >= r) return moves;
    if (moves > k) return IMAX; // prune moves > 20

    if (v[l] == v[r])
        return solve(l+1,r-1,moves);
    else
        return min(solve(l+1,r,moves+1), solve(l,r-1,moves+1));
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case " << t << ": ";
        cin >> n >> k;
        for (int i = 0; i < n; ++i)
            cin >> v[i];
        int ans = solve(0,n-1,0);
        if (ans == 0) {
            cout << "Too easy" << endl;
        } else if (ans > k) {
            cout << "Too difficult" << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}