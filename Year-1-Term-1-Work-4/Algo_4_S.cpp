#include <bits/stdc++.h>
#define pll pair<ll, ll>

using namespace std;
typedef long long ll;
const int inf = 1e9 + 7;
const int mod = 999999937;

const vector <vector <ll> > e = {{1, 1, 1, 1, 1},
			   {1, 1, 1, 1, 1},
			   {1, 1, 1, 1, 1},
			   {1, 1, 0, 1, 0},
			   {1, 1, 0, 1, 0}};

vector <vector <ll> > dp0(5, vector <ll> (1, 1));

vector <vector <ll> > mul(vector <vector <ll> > a, vector <vector <ll> > b) {
	if (a[0].size() != b.size()) {
		cout << "Я проиграл";
	}
	int n = (int)a.size(), k = (int)a[0].size(), m = (int)b[0].size();
	vector <vector <ll> > ans(n, vector <ll> (m, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			for (int t = 0; t < k; ++t) {
				ans[i][j] += a[i][t] * b[t][j];
				ans[i][j] %= mod;
			}
	return ans;
}

vector <vector <ll> > pow(vector <vector <ll> > dp, ll n) {
	if (n == 1)
		return dp;
	if (n % 2 == 0) {
		vector <vector <ll> > b = pow(dp, n / 2);
		return mul(b, b);
	}
	return mul(dp, pow(dp, n - 1));
}

int main() {
    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);
	ll n;
	while (1) {
		cin >> n;
		if (n == 0)
			return 0;
		if (n == 1) {
			cout << 5 << endl;
			continue;
		} else {
			n--;
		}
	    vector <vector <ll> > dp = mul(pow(e, n), dp0);
    	ll ans = 0;
		for (int i = 0; i < (int)dp.size(); ++i)
    		for (int j = 0; j < (int)dp[i].size(); ++j) {
    			ans += dp[i][j];
    			ans %= mod;
    		}
		cout << ans << endl;
	}
    return 0;
}
