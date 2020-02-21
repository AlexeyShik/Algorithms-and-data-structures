#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll inf = 1e15;

int main() {
	freopen("salesman.in", "r", stdin);
	freopen("salesman.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector <vector <pair <int, ll> > > gr(n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--, v--;
		gr[u].push_back({v, w});
		gr[v].push_back({u, w});
	}
	vector <vector <ll> > dp((1 << n), vector <ll> (n, inf));
	vector <vector <int> > par((1 << n), vector <int> (n, -1));
	for (int i = 0; i < n; ++i)
		dp[(1 << i)][i] = 0;
	for (int mask = 1; mask < (1 << n); ++mask)
		for (int v = 0; v < n; ++v)
			if (dp[mask][v] != inf)
				for (auto u : gr[v])
					if ((mask & (1 << u.first)) == 0 &&
					dp[mask | (1 << u.first)][u.first] > dp[mask][v] + u.second) {
						dp[mask | (1 << u.first)][u.first] = dp[mask][v] + u.second;
						par[mask | (1 << u.first)][u.first] = v;
					}
	ll ans = inf;
	int u = -1, mask = (1 << n) - 1;
	for (int v = 0; v < n; ++v)
		if (ans > dp[mask][v]) {
			ans = dp[mask][v];
			u = v;
		}
	vector <int> path;
	while (u != -1) {
		path.push_back(u);
		mask &= (~(1 << u));
		u = par[mask | (1 << u)][u];
	}
	cout << (ans == inf ? -1 : ans) << endl;
	return 0;
}
