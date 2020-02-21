#include <bits/stdc++.h>

using namespace std;
vector <int> tmp;

int quickSort(int l, int r, int k, vector <int> &v) {
	if (l + 1 == r)
		return (k == 0 ? v[l] : v[r]);
	int x = v[(l + r) / 2];
	int ptr1 = l, ptr2 = r - 1;
	for (int i = l; i < r; ++i)
		if (v[i] < x)
			tmp[ptr1++] = v[i];
		else if (v[i] > x)
			tmp[ptr2--] = v[i];
	for (int i = l; i < ptr1; ++i)
		v[i] = tmp[i];
	for (int i = ptr2 + 1; i < r; ++i)
		v[i] = tmp[i];
	if (k + l >= ptr1 && k + l <= ptr2)
		return x;
	if (ptr1 - l > k)
		return quickSort(l, ptr1, k, v);
	return quickSort(ptr2 + 1, r, k - (ptr2 + 1 - l), v);
}

int main() {
	int n, k;
	cin >> n >> k;
	vector <int> v(n);
	tmp.resize(n, 0);
	int a, b, c;
	cin >> a >> b >> c >> v[0] >> v[1];
	for (int i = 2; i < n; ++i)
		v[i] = a * v[i - 2] + b * v[i - 1] + c;
	cout << quickSort(0, n, k - 1, v);
	return 0;
}
