#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
vector <ll> tmp1, tmp2, tmp3;

void mergeSort(int l, int r, ll T, vector <ll> &a, vector <ll> &b, vector <ll> &t) {
	if (l + 1 >= r)
		return;
	int m = (l + r) / 2;
	mergeSort(l, m, T, a, b, t);
	mergeSort(m, r, T, a, b, t);
	int ptr1 = l, ptr2 = m;
	for (int i = l; i < r; ++i) {
		if (ptr1 == m) {
			tmp1[i] = a[ptr2];
			tmp2[i] = b[ptr2];
			tmp3[i] = t[ptr2];
			ptr2++;
		} else if (ptr2 == r) {
			tmp1[i] = a[ptr1];
			tmp2[i] = b[ptr1];
			tmp3[i] = t[ptr1];
			ptr1++;
		} else if ((T - t[ptr1] - b[ptr1]) * a[ptr2] <= (T - t[ptr2] - b[ptr2]) * a[ptr1]) {
			tmp1[i] = a[ptr1];
			tmp2[i] = b[ptr1];
			tmp3[i] = t[ptr1];
			ptr1++;
		} else {
			tmp1[i] = a[ptr2];
			tmp2[i] = b[ptr2];
			tmp3[i] = t[ptr2];
			ptr2++;
		}
	}
	for (int i = l; i < r; ++i) {
		a[i] = tmp1[i];
		b[i] = tmp2[i];
		t[i] = tmp3[i];
	}
}

int main() {
	int m, n, p;
	cin >> m;
	vector <ll> a(m), b(m), t(m);
	tmp1.resize(m);
	tmp2.resize(m);
	tmp3.resize(m);
	for (int i = 0; i < m; ++i)
		cin >> a[i] >> b[i] >> t[i];
	cin >> n >> p;
	if (p == 0) {
		cout << 0;
		return 0;
	}
	ll l = 0, r = 1e16;
	for (int i = 0; i < m; ++i)
		if (a[i] == 0)
			r = min(r, t[i] + b[i]);
	while (r - l > 1) {
		ll T = (l + r) / 2;
		mergeSort(0, m, T, a, b, t);
		ll cnt = 0;
		int usedPeople = 0;
		for (int i = m - 1; i >= 0; --i) {
			ll curt = T - t[i] - b[i];
			if (curt <= 0)
				continue;
			if (a[i] > 0) {
				cnt += curt / a[i];
				usedPeople++;
			}
			if (usedPeople == n)
				break;
		}
		if (cnt >= p)
			r = T;
		else
			l = T;
	}
	cout << r;
	return 0;
}
