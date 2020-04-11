#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll LMAX = (1LL<<61);
const int IMAX = (1<<29);
const int BIG = 104206970;
const int PRIME = 104206969;

const int N = 11;

int n;
vector<int> diviors;
vector<vector<int>> ans;

void dfs (int x, int idx, vector<int> running) {
	if (x == 1) {
		ans.push_back(running);
	} else {
		for (int i = idx; i < diviors.size(); i++) {
			if (x%diviors[i] == 0 and (x/diviors[i] >= diviors[i] or x == diviors[i])) {
				running.push_back(diviors[i]);
				dfs(x/diviors[i], i, running);
				running.pop_back();
			}
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(9); cout << fixed;
	while (1) {
		cin >> n;
		if (n == 0)
			break;
		for (int i = 2; i*i <= n; i++) {
			if (n%i == 0) {
				diviors.push_back(i);
				if (i*i < n)
					diviors.push_back(n/i);
			}
		}
		sort(diviors.begin(),diviors.end());
		int solutions = 0;
		vector<int> empty;
		if (diviors.size() > 0) {
			dfs(n,0,empty);
		}
		cout << ans.size() << endl;
		for (vector<int> v : ans) {
			for (int i = 0; i < v.size(); i++) {
				cout << v[i] << (i+1 == v.size() ? '\n' : ' ');
			}
		}
		ans.clear();
		diviors.clear();
	}
	return 0;
}