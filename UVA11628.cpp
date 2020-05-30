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

int n, m, v[N];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0);
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        int tmp;
        int tot = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m-1; ++j) {
                cin >> tmp; // lmao all other inputs dont matter
            }
            cin >> v[i]; tot += v[i];
        }

        for (int i = 0; i < n; ++i) {
            if (v[i] == 0) {
                cout << "0 / 1" << endl;
            } else {
                if (tot > 0)
                    cout << v[i]/__gcd(v[i],tot) << " / " << tot/__gcd(v[i],tot) << endl;
                else
                    cout << "0 / 1" << endl;
            }
        }
        
    }
    return 0;
}