#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


int main() {
	int n;
	cin >> n;
	vector <int> v(n);
	bool ans = true;
	cin >> v[0];
	for (int i = 1; i < n; ++i) {
		cin >> v[i];
		ans &= v[i] >= v[(i - 1) / 2];
	}
	cout << (ans ? "YES" : "NO");
	return 0;
}
