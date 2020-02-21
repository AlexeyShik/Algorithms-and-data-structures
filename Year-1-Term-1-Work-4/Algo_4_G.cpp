#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pii pair<int, int>

using namespace std;
typedef long long ll;
const int inf = 1e9 + 7;

int main() {
    freopen("meetings.in", "r", stdin);
	freopen("meetings.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector <pair <pii, int> > event(n);
    for (int i = 0; i < n; ++i)
    	cin >> event[i].first.first >> event[i].first.second >> event[i].second;
    vector <set <pii> > dp(1 << n);
    dp[0].insert({k, -1});
    for (int mask = 1; mask < (1 << n); ++mask) {
    	for (int i = 0; i < n; ++i) {
    		int prev = mask & (~(1 << i));
    		if (prev == mask)
    			continue;
    		for (auto curr : dp[prev])
    			if (event[i].first.first <= curr.first && curr.first <= event[i].first.second)
    				dp[mask].insert({curr.first + event[i].second, i});
		}
	}
	int best = 0, best_mask = -1;
	for (int mask = 1; mask < (1 << n); ++mask) {
		if (!dp[mask].empty() && __builtin_popcount(mask) >= best) {
			best = __builtin_popcount(mask);
			best_mask = mask;
		}
	}
	vector <int> path;
	if (best_mask == -1) {
		cout << 0;
		return 0;
	}
	int id = dp[best_mask].begin()->second;
	int bal = dp[best_mask].begin()->first;
	while (id != -1) {
		path.push_back(id);
		bal -= event[id].second;
		best_mask = best_mask & (~(1 << id));
		for (auto pp : dp[best_mask])
			if (pp.first == bal) {
				id = pp.second;
				break;
			}
	}
	cout << path.size() << endl;
	reverse(path.begin(), path.end());
	for (int x : path)
		cout << x + 1 << ' ';
    return 0;
}
