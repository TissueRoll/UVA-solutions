#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5+7;
const ll MOD = 2000000011;

int T, dp[N];
string s;
stack<pair<char,int>> paren;
map<char,char> matching;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	matching['('] = ')';
	matching['['] = ']';
	matching['{'] = '}';
	matching['<'] = '>';
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cin >> s; 
		dp[s.size()] = 0;
		for (int i = 0; i < s.size(); ++i) {
			dp[i] = 0;
			if (s[i] == '(' or s[i] == '[' or s[i] == '{' or s[i] == '<') {
				paren.push({s[i],i});
			} else if (not paren.empty() and matching[paren.top().first] == s[i]) {
				pair<char,int> tmp = paren.top(); paren.pop();
				dp[tmp.second] = max(dp[tmp.second], i-tmp.second+1);
			} else {
				while (not paren.empty())
					paren.pop();
			}
		}

		for (int i = s.size()-1; i >= 0; --i) {
			dp[i] = dp[i] + dp[i +dp[i]];
		}

		cout << "Case " << t << ":\n";
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(' or s[i] == '[' or s[i] == '{' or s[i] == '<') {
				cout << dp[i] << endl;
			} else {
				cout << 0 << endl;
			}
		}
		while (not paren.empty())
			paren.pop();
	}
	return 0;
}
