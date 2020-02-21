#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9 + 7;

int main() {
	freopen("lis.in", "r", stdin);
	freopen("lis.out", "w", stdout);
	int n;
	cin >> n;
	vector <int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	vector <int> dp(n, inf), dp_id(n, -1), prev(n, -1);
	dp[0] = v[0]; dp_id[0] = 0;
	for (int i = 1; i < n; ++i) {
		int j = upper_bound(dp.begin(), dp.end(), v[i]) - dp.begin();
		if ((j == 0 || dp[j - 1] < v[i]) && v[i] < dp[j]) {
			dp[j] = v[i];
			dp_id[j] = i;
			prev[i] = (j > 0 ? (int)dp_id[j - 1] : -1);
		}
	}
	int pos;
	for (pos = n - 1; pos >= 0; --pos)
		if (dp[pos] != inf) {
			cout << pos + 1 << endl;
			break;
		}
	pos = (int)dp_id[pos];
	vector <int> path;
	while (pos >= 0) {
		path.push_back(v[pos]);
		pos = (int)prev[pos];
	}
	reverse(path.begin(), path.end());
	for (auto x : path)
		cout << x << ' ';
	return 0;
}
