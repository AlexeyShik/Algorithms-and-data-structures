#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
	ll n = 1e18;
	ll x, m;
	cin >> x >> m;
	cout << "? 1" << endl;
	ll y;
	cin >> y;
	ll d = y - 1;
	x -= d;
	if (x < 1)
		x += n;
	ll l = max(1ll, x - m), r = min(x, n - m) + 1;
	ll cur = y, qmid = 1;
	for (int i = 0; i < 9; ++i) {
		qmid = (l + r) / 2;
		cout << "? " << qmid << endl;
		cin >> cur;
		cur -= d;
		if (cur < 1)
			cur += n;
		if (cur == x) {
			cout << "! " << qmid << endl;
			return 0;
		}
		if (cur < x)
			l = qmid;
		else
			r = qmid;
	}
	if (cur != x)
		cout << "! -1" << endl;
	else
		cout << "! " << qmid << endl;
	return 0;
}
