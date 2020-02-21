#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector <int> nxt, sz;
int n, k = 0;

inline int leader(int i) {
	if (sz[i] == 1) {
		return nxt[i];
	}
	int j = leader(nxt[i]);
	sz[i]++;
	return nxt[i] = j;
}

inline void Set(int u) {
	u = leader(u);
	sz[u] = 2;
	cout << u + 1 << ' ';
	if (k == n)
		return;
	int v = leader((u + 1) % n);
	nxt[u] = v;
}

int main() {
	cin >> n;
	nxt.resize(n);
	sz.resize(n, 1);
	for (int i = 0; i < n; ++i)
		nxt[i] = i;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		x--;
		++k;
		Set(x);
	}
	return 0;
}
