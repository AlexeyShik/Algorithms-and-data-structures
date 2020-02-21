#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = (int)1e9;

int main() {
	int n;
	cin >> n;
	vector <ll> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	vector <vector <ll> > dp(n, vector <ll> (n));
	for (int i = 0; i < n; ++i)
		dp[i][i] = 1;
	for (int len = 1; len < n; ++len)
		for (int l = 0; l + len < n; ++l)
			dp[l][l + len] = (dp[l + 1][l + len] + dp[l][l + len - 1] + mod - dp[l + 1][l + len - 1] + (v[l] == v[l + len]) * (dp[l + 1][l + len - 1] + 1)) % mod;
	cout << dp[0][n - 1];
	return 0;
}
