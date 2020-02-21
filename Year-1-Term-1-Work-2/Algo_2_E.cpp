#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	vector <string> v(n), sub(n);
	vector <int> h(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	map <string, int> t, pref;
	for (int i = 0; i < n; ++i) {
		sub[i] = v[i].substr(m - k, k);
		t[sub[i]]++;
	}
	pref[t.begin()->first] = t.begin()->second;
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto nit = it;
		++nit;
		if (nit == t.end())
			break;
		pref[nit->first] = pref[it->first] + nit->second;
	}
	for (int i = 0; i < n; ++i) {
		h[i] = pref[sub[i]] - t[sub[i]];
		t[sub[i]]--;
	}
	vector <string> ans(n);
	for (int i = 0; i < n; ++i) {
		ans[h[i]] = v[i];
	}
	for (auto x : ans)
		cout << x << endl;
	return 0;
}
