#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int N = 20;
const int BIG_N = (1<<N);

int T, n, m, nums;
pii start, beepers[N];

int manhattan_distance(pii a, pii b) {
	return abs(a.first-b.first)+abs(a.second-b.second);
}

int main () {
	cin >> T;
	while (T--) {
		cin >> n >> m;
		cin >> start.first >> start.second;
		cin >> nums;
		for (int i = 0; i < nums; i++) cin >> beepers[i].first >> beepers[i].second;
		int ans = 0x3f3f3f3f;
		do {
			int temp = 0;
			temp += manhattan_distance(start, beepers[0]);
			for (int i = 1; i < nums; i++) temp += manhattan_distance(beepers[i-1],beepers[i]);
			temp += manhattan_distance(start, beepers[nums-1]);
			ans = min(temp,ans);
		}while(next_permutation(beepers,beepers+nums));
		printf("The shortest path has length %d\n", ans);
	}

	return 0;
}