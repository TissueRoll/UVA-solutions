#include <bits/stdc++.h>
using namespace std;

int main () {
	int n, m;
	while (1) {
		cin >> n >> m;
		if (n == 0 and m == 0)
			break;
		int heads[n], warriors[m];
		for (int i = 0; i < n; i++)
			cin >> heads[i];
		for (int i = 0; i < m; i++)
			cin >> warriors[i];
		sort(heads, heads+n);
		sort(warriors, warriors+m);
		int cur = 0;
		int ans = 0;
		int selected = 0;
		for (int head = 0; head < n; head++) {
			for (; cur < m; cur++) {
				if (heads[head] <= warriors[cur]) {
					selected++;
					ans += warriors[cur++];
					break;
				}
			}
		}

		if (n > m or selected < n)
			cout << "Loowater is doomed!" << endl;
		else
			cout << ans << endl;
	}
	return 0;
}
