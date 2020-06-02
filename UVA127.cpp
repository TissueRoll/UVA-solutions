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

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s;
    while (true) {
        vector<stack<string>> deck(52);
        for (int i = 0; i < 52; ++i) {
            cin >> s;
            if (s == "#") return 0;
            deck[i].push(s);
        }

        int stacks = 52;

        bool move_made = 1;
        while (move_made) {
            move_made = 0;
            for (int i = 1; i < stacks and not move_made; ++i) {
                string cur_card = deck[i].top();
                string left_card = deck[i-1].top();
                string third_to_left_card = "##";
                if (i > 2)
                    third_to_left_card = deck[i-3].top();
                if (cur_card[0] == third_to_left_card[0] or cur_card[1] == third_to_left_card[1]) {
                    move_made = 1;
                    deck[i].pop();
                    if (deck[i].empty()) {
                        // move everything left
                        for (int j = i+1; j < stacks; ++j) {
                            deck[j-1] = deck[j];
                        }
                        stacks--;
                    }
                    deck[i-3].push(cur_card);
                    break;
                } else if (cur_card[0] == left_card[0] or cur_card[1] == left_card[1]) {
                    move_made = 1;
                    deck[i].pop();
                    if (deck[i].empty()) {
                        // move everything left
                        for (int j = i+1; j < stacks; ++j) {
                            deck[j-1] = deck[j];
                        }
                        stacks--;
                    }
                    deck[i-1].push(cur_card);
                    break;
                }
            }
        }

        cout << stacks << " pile" << (stacks != 1 ? "s" : "") << " remaining:";
        for (int i = 0; i < stacks; ++i) {
            cout << " " << deck[i].size();
        }
        cout << endl;

    }

    return 0;
}