#include <bits/stdc++.h>
#define pll pair<ll, ll>

using namespace std;
typedef long long ll;
const int inf = 1e9 + 7;
vector <vector <ll> > dp;
vector <pll> v;

void print(int l, int r) {
	if (l == r) {
		cout << 'A';
		return;
	}
	if (l + 1 == r) {
		cout << "(AA)";
		return;
	}
	cout << '(';
	for (int k = l; k < r; ++k) {
		if (dp[l][r] == dp[l][k] + dp[k + 1][r] + v[l].first * v[k].second * v[r].second) {
			print(l, k);
			print(k + 1, r);
			break;
		}
	}
	cout << ')';
}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    int n;
    cin >> n;
    v.resize(n);
    dp.resize(n, vector <ll> (n, 1e9));
    for (int i = 0; i < n; ++i)
        cin >> v[i].first >> v[i].second;
    for (int l = 0; l < n; ++l)
    	dp[l][l] = 0;
    for (int len = 1; len < n; ++len)
        for (int l = 0; l < n - len; ++l) {
            int r = l + len;
            if (l + 1 == r) {
            	dp[l][r] = v[l].first * v[l].second * v[r].second;
            	continue;
			}
            for (int k = l; k < r; ++k)
            	dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]
				+ v[l].first * v[k].second * v[r].second);
        }
    print(0, n - 1);
    return 0;
}

/*
3
10 50
50 90
90 20
*/
