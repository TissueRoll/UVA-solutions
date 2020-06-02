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
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

ll a[N], b[N], dp[N][N], path[N][N];

ll solve (int l, int r) { // literally break the problem in pieces
    if (l == r)
        return 0;
    ll &ans = dp[l][r];
    if (ans != -1)
        return ans;
    ans = LLMAX;
    for (int i = l; i < r; ++i) {
        ll tmp = solve(l,i) + solve(i+1,r) + a[l]*b[i]*b[r];
        if (tmp < ans) {
            ans = tmp;
            path[l][r] = i;
        }
    }
    return ans;
}

void print_path(int l, int r) {
    if (l == r) {
        cout << "A" << l+1;
    } else {
        cout << "(";
        print_path(l,path[l][r]);
        cout << " x ";
        print_path(path[l][r]+1,r);
        cout << ")";
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T = 1;
    while (true) {
        int n; cin >> n;
        if (n == 0)
            break;
        cout << "Case " << T++ << ": ";
        for (int i = 0; i < n; ++i)
            cin >> a[i] >> b[i];
        memset(dp, -1, sizeof dp);
        memset(path, -1, sizeof path);
        solve(0,n-1);
        print_path(0,n-1);
        cout << endl;
    }    

    return 0;
}