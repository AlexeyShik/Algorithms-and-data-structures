#include <bits/stdc++.h>

using namespace std;

int main() {
	string s, t;
	cin >> t >> s;
	int n = (int)s.size(), m = (int)t.size();
	s = '#' + s;
	t = '#' + t;
	vector <vector <bool> > dp(n + 1, vector <bool> (m + 1, false));
	vector <vector <bool> > predp(n + 1, vector <bool> (m + 1, false));
	dp[0][0] = predp[0][0] = true;
	for (int i = 0; i <= n; ++i)
		predp[i][0] = true;
	int f = 1;
	while (f < (int)t.size() && t[f] == '*') {
		predp[0][f] = dp[0][f] = true;
		++f;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (t[j] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
			} else if (t[j] == '*') {
				dp[i][j] = predp[i][j - 1];
			} else {
				dp[i][j] = dp[i - 1][j - 1] && (s[i] == t[j]);
			}
			predp[i][j] = predp[i - 1][j] || dp[i][j];
		}
	}
	cout << (dp[n][m] ? "YES" : "NO");
	return 0;
}
