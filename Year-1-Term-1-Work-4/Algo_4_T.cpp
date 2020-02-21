#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pii pair<int, int>

using namespace std;
typedef long long ll;

int n;
vector <ll> sz, down, up;
vector <vector <pii> > g;
vector <ll> ans;

void calc_sizes(int v, int p) {
	sz[v] = 1;
	for (pii u : g[v])
		if (u.first != p) {
			calc_sizes(u.first, v);
			sz[v] += sz[u.first];
		}
}

void dfs_down(int v, int p) {
	down[v] = sz[v];
	for (pii u : g[v])
		if (u.first != p) {
			dfs_down(u.first, v);
			down[v] += down[u.first];
		}
}

void dfs_up(int v, int p) {
	up[v] += (p == -1 ? 0 : up[p]) + (n - sz[v]);
	ll sum = 0;
	for (pii u : g[v])
		if (u.first != p)
			sum += down[u.first];
	for (pii u : g[v])
		if (u.first != p) {
			up[u.first] = sum - down[u.first];
			dfs_up(u.first, v);
		}
	for (pii u : g[v])
		if (u.first == p && p != -1)
			ans[u.second] = down[v] * (n - sz[v]) + sz[v] * (up[v] - (n - sz[v]));
}

int main() {
	freopen("treedp.in", "r", stdin);
	freopen("treedp.out", "w", stdout);
	fastio;
	cin >> n;
	sz.resize(n, 0);
	down.resize(n, 0);
	up.resize(n, 0);
	g.resize(n);
	ans.resize(n);
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back({v, i - 1});
		g[v].push_back({u, i - 1});
	}
	calc_sizes(0, -1);
	dfs_down(0, -1);
	dfs_up(0, -1);
	for (int i = 0; i + 1 < n; ++i)
		cout << ans[i] << endl;
	return 0;
}
