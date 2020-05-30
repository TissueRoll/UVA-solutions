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

const int N = 200001;
const int NN = 1000001;
const int IMAX = 1e9+7;

int n, vsz[30], v[30][30];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
    memset(v, -1, sizeof v);
	cin >> n;
    for (int i = 0; i < n; ++i) {
        v[i][0] = i;
        vsz[i] = 1;
    }
    string command;
    while (true) {
        cin >> command;
        if (command == "quit") break;
        int a, b; string where; cin >> a >> where >> b;
        // getting a and b location
        int aloc, bloc;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < vsz[i]; ++j) {
                if (v[i][j] == a) aloc = i;
                if (v[i][j] == b) bloc = i;
            }
        }
        if (aloc == bloc) continue;

        // getting things a and b above
        queue<int> aq, bq;
        int afound = -1, bfound = -1;
        for (int i = 0; i < vsz[aloc]; ++i) {
            if (v[aloc][i] == a) {
                afound = i;
            }
            if (afound != -1) {
                aq.push(v[aloc][i]);
            }
        }

        for (int i = 0; i < vsz[bloc]; ++i) {
            if (v[bloc][i] == b) {
                bfound = i;
            }
            if (bfound != -1) {
                bq.push(v[bloc][i]);
            }
        }

        // cout << aq.size() << ' ' << bq.size() << endl;

        assert(afound != -1);
        assert(bfound != -1);

        if (command == "move") {
            if (where == "onto") {
                for (int i = afound; i < vsz[aloc]; ++i) {
                    v[aloc][i] = -1;
                }
                vsz[aloc] -= aq.size();
                for (int i = bfound+1; i < vsz[bloc]; ++i) {
                    v[bloc][i] = -1;
                }
                vsz[bloc] -= (bq.size()-1);
                aq.pop();
                while (not aq.empty()) {
                    v[aq.front()][vsz[aq.front()]++] = aq.front();
                    aq.pop();
                }
                bq.pop();
                while (not bq.empty()) {
                    v[bq.front()][vsz[bq.front()]++] = bq.front();
                    bq.pop();
                }
                v[bloc][vsz[bloc]++] = a;
            } else {
                for (int i = afound; i < vsz[aloc]; ++i) {
                    v[aloc][i] = -1;
                }
                vsz[aloc] -= aq.size();
                v[bloc][vsz[bloc]++] = a;
                aq.pop();
                while (not aq.empty()) {
                    v[aq.front()][vsz[aq.front()]++] = aq.front();
                    aq.pop();
                }
            }
        } else { // pile
            if (where == "onto") {
                for (int i = afound; i < vsz[aloc]; ++i) {
                    v[aloc][i] = -1;
                }
                vsz[aloc] -= aq.size();
                for (int i = bfound+1; i < vsz[bloc]; ++i) {
                    v[bloc][i] = -1;
                }
                vsz[bloc] -= (bq.size()-1);
                while (not aq.empty()) {
                    v[bloc][vsz[bloc]++] = aq.front();
                    aq.pop();
                }
                bq.pop();
                while (not bq.empty()) {
                    v[bq.front()][vsz[bq.front()]++] = bq.front();
                    bq.pop();
                }
            } else {
                for (int i = afound; i < vsz[aloc]; ++i) {
                    v[aloc][i] = -1;
                }
                vsz[aloc] -= aq.size();
                while (not aq.empty()) {
                    v[bloc][vsz[bloc]++] = aq.front();
                    aq.pop();
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int j = 0; j < vsz[i]; ++j) {
            cout << " " << v[i][j];
        }
        cout << endl;
    }

	return 0;
}