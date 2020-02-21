#include <bits/stdc++.h>

using namespace std;
vector <int> tmp;

void mergeSort(int l, int r, vector <int> &v) {
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

int main() {
	int n;
	cin >> n;
	tmp.resize(n, 0);
	vector <int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	mergeSort(0, n, v);
	for (int x : v)
		cout << x << ' ';
	return 0;
}
