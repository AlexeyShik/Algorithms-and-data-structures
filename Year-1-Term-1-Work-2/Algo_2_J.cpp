#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector <ll> tmp;
ll ans = 0, k;

void mergeSort(int l, int r, vector <ll> &v) {
	if (l + 1 >= r)
		return;
	int m = (l + r) / 2;
	mergeSort(l, m, v);
	mergeSort(m, r, v);
	int ptr1 = l, ptr2 = m, h = m;
	for (int i = l; i < r; ++i) {
		if (ptr2 == r) {
			while (h < r && v[h] - v[ptr1] < k) {
				h++;
			}
			ans += r - h;
			tmp[i] = v[ptr1];
			ptr1++;
		}
		else
		if (ptr1 == m) {
			tmp[i] = v[ptr2];
			ptr2++;
		}
		else
		if (v[ptr1] <= v[ptr2]) {
			while (h < r && v[h] - v[ptr1] < k) {
				h++;
			}
			ans += r - h;
			tmp[i] = v[ptr1];
			ptr1++;
		} else {
			tmp[i] = v[ptr2];
			ptr2++;
		}
	}
	for (int i = l; i < r; ++i)
		v[i] = tmp[i];
}

int n;
unsigned int a, b;
unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

unsigned int nextRand32() {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}

int main() {
	cin >> n >> k >> a >> b;
	tmp.resize(n + 1, 0);
	vector <ll> v(n + 1), f(n);
	v[0] = 0;
	for (int i = 0; i < n; ++i) {
		v[i + 1] = (int)nextRand32();
		v[i + 1] += v[i];
	}
	mergeSort(0, n + 1, v);
	cout << ans;
	return 0;
}
