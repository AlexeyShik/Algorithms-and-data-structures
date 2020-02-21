#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll lowerBound(ll x, vector <ll> &v) {
	int l = 0, r = v.size();  // v[r] >= x, v[l] < x
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (v[m] < x)
			l = m;
		else
			r = m;
	}
	if (v[l] == x)
		return l + 1;
	if (v[r] == x)
		return r + 1;
	return -1;
}

ll upperBound(ll x, vector <ll> &v) {
	int l = 0, r = v.size();  // v[r] > x, v[l] <= x
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (v[m] <= x)
			l = m;
		else
			r = m;
	}
	if (v[r] == x)
		return r + 1;
	if (v[l] == x)
		return l + 1;
	return -1;
}

int main() {
	int n;
	cin >> n;
	vector <ll> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	int m;
	cin >> m;
	while (m--) {
		ll x;
		cin >> x;
		cout << lowerBound(x, v) << ' ' << upperBound(x, v) << endl;
	}
	return 0;
}
