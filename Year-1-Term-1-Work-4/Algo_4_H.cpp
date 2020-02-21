#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

inline ll gcd(ll a, ll b) {
    return (a == 0 ? b : gcd(b % a, a));
}

int main() {
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
    int n;
	ll m, k;
    cin >> n >> m >> k;
    vector <ll> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    sort(v.begin(), v.end());
    vector <vector <vector <ll> > > dp((1 << n), vector <vector <ll> > (n, vector <ll> (n, 0ll)));
    vector <vector <bool> > gg(n, vector <bool> (n, false));
    for (int i = 0; i < n; ++i)
    	for (int j = 0; j < n; ++j)
    		gg[i][j] = (gcd(v[i], v[j]) >= k);
    for (int i = 0; i < n; ++i)
        dp[1 << i][i][i] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j  && gg[i][j]) {
                dp[(1 << i) | (1 << j)][i][j] = 1;
            }
        }
    }
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if ((mask & (1 << i)) == 0)
                continue;
            for (int j = 0; j < n; ++j) {
                if ((mask & (1 << j)) == 0 || j == i)
                    continue;
                int prev = mask ^ (1 << j);
                for (int l = 0; l < n; ++l) {
                    if ((prev & (1 << l)) == 0 || !gg[j][l] || l == i || l == j)
                        continue;
                    dp[mask][i][j] += dp[prev][i][l];
                }
            }
        }
    }
    int mask = (1 << n) - 1;
    vector <ll> ans;
    int beg = -1, prev_beg = -1;
    for (int t = 0; t + 1 < n; ++t) {
    	for (int i = 0; i < n; ++i) {
    		if ((mask & (1 << i)) == 0 || (beg != -1 && !gg[beg][i]))
    			continue;
    		ll inc = 0;
    	    for (int j = 0; j < n; ++j) {
    	    	if (i != j && (mask & (1 << j)) != 0)
            		inc += dp[mask][i][j];
        	}
        	if (inc >= m) {
        		prev_beg = beg;
        		mask ^= (1 << i);
        		beg = i;
        		break;
			} else {
				m -= inc;
			}
        }
        if (beg == prev_beg) {
        	cout << -1;
        	return 0;
    	}
    	ans.push_back(v[beg]);
    }
    for (int i = 0; i < n; ++i) {
    	if ((mask & (1 << i)) != 0) {
    		ans.push_back(v[i]);
    	}
    }
    if ((int)ans.size() != n || m != 1) {
    	cout << -1;
    	return 0;
	}
    for (ll x : ans)
        cout << x << ' ';
    return 0;
}
