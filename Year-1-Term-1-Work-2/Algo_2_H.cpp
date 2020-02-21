#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector <ll> tmp;
ll inverses = 0;

void mergeSort(int l, int r, vector <ll> &v) {
	if (l + 1 >= r)
		return;
	int m = (l + r) / 2;
	mergeSort(l, m, v);
	mergeSort(m, r, v);
	int ptr1 = l, ptr2 = m;
	for (int i = l; i < r; ++i) {
		if (ptr1 == m) {
			tmp[i] = v[ptr2];
			ptr2++;
		} else if (ptr2 == r) {
			tmp[i] = v[ptr1];
			ptr1++;
		} else if (v[ptr1] <= v[ptr2]) {
			tmp[i] = v[ptr1];
			ptr1++;
		} else {
			inverses += m - ptr1;
			tmp[i] = v[ptr2];
			ptr2++;
		}
	}
	for (int i = l; i < r; ++i)
		v[i] = tmp[i];
}

int n;
ll m;
unsigned int a, b;
unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

int main() {
	cin >> n >> m >> a >> b;
	tmp.resize(n, 0);
	vector <ll> v(n);
	for (int i = 0; i < n; ++i)
		v[i] = nextRand24() % m;
	mergeSort(0, n, v);
	cout << inverses;
	return 0;
}
