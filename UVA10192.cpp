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

const int N = 100005;
const int NN = 10000001;
const int IMAX = 1e9+7;

string mader, pader;
int dp[101][101];

int lcs (int n, int m) {
	int& ans = dp[n][m];
	if (ans != -1)
		return ans;
	if (n == 0 or m == 0)
		ans = 0;
	else if (mader[n-1] == pader[m-1]) // same
		ans = 1+lcs(n-1, m-1);
	else // not same
		ans = max(lcs(n,m-1), lcs(n-1,m));
	return ans;
}

int main () {
	int T = 1;
	while (true) {
		getline(cin, mader);
		if (mader == "#") break;
		getline(cin, pader);
		memset(dp, -1, sizeof dp);
		cout << "Case #" << T++ << ": you can visit at most " << lcs(mader.size(), pader.size()) << " cities.\n";
	}	
	return 0;
}