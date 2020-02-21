#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
vector <ld> tmp;
vector <pair <ld, int> > tmp1;

void mergeSort(int l, int r, vector <ld> &v) {
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
			tmp[i] = v[ptr2];
			ptr2++;
		}
	}
	for (int i = l; i < r; ++i)
		v[i] = tmp[i];
}

void mergePairSort(int l, int r, vector <pair <ld, int> > &v) {
	if (l + 1 >= r)
		return;
	int m = (l + r) / 2;
	mergePairSort(l, m, v);
	mergePairSort(m, r, v);
	int ptr1 = l, ptr2 = m;
	for (int i = l; i < r; ++i) {
		if (ptr1 == m) {
			tmp1[i] = v[ptr2];
			ptr2++;
		} else if (ptr2 == r) {
			tmp1[i] = v[ptr1];
			ptr1++;
		} else if (v[ptr1].first <= v[ptr2].first) {
			tmp1[i] = v[ptr1];
			ptr1++;
		} else {
			tmp1[i] = v[ptr2];
			ptr2++;
		}
	}
	for (int i = l; i < r; ++i)
		v[i] = tmp1[i];
}

int main() {
	int n, k;
	cin >> n >> k;
	vector <ld> v(n), w(n);
	tmp.resize(n);
	tmp1.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i] >> w[i];
	ld l = 0, r = 1e9;
	const ld eps = 1e-7;
	while (r - l > eps) {
		ld m = (l + r) / 2;
		vector <ld> rem(n);
		for (int i = 0; i < n; ++i)
			rem[i] = v[i] - w[i] * m;
		mergeSort(0, n, rem);
		ld sum = 0;
		for (int i = n - k; i < n; ++i)
			sum += rem[i];
		if (sum >= 0)
			l = m;
		else
			r = m;
	}
	vector <pair <ld, int> > best(n);
	for (int i = 0; i < n; ++i) {
		best[i].first = v[i] - w[i] * l;
		best[i].second = i + 1;
	}
	mergePairSort(0, n, best);
	vector <ld> index(k);
	for (int i = n - 1; i >= n - k; --i)
		index[n - i - 1] = best[i].second;
	mergeSort(0, k, index);
	for (int i = 0; i < k; ++i)
		cout << index[i] << ' ';
	return 0;
}
