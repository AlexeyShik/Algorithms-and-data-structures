#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

unsigned int a, b;
unsigned int cur = 0;
inline unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

inline unsigned int nextRand32() {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}

int main() {
	const int base = 1626;
	const int maxn = 100000;
	int tt = 200, n = maxn;
	cin >> tt >> n;
	unsigned int v[maxn] = {0}, tmp[maxn] = {0}, pw[3];
	pw[0] = 1;
	pw[1] = base;
	pw[2] = pw[1] * base;
	unsigned int sub[maxn] = {0};
	while (tt--) {
		cin >> a >> b;
		for (int i = 0; i < n; ++i)
			v[i] = nextRand32();
		for (int k = 0; k < 3; ++k) {
			int t[base] = {0};
			for (int i = 0; i < n; ++i) {
				sub[i] = (v[i] / pw[k]) % base;
				t[(size_t)sub[i]]++;
			}
			int count = 0;
			for (int i = 0; i < base; ++i) {
				int c = t[i];
				t[i] = count;
				count += c;
			}
			for (int i = 0; i < n; ++i) {
				tmp[t[sub[i]]] = v[i];
				t[sub[i]]++;
			}
			swap(v, tmp);
		}
		unsigned long long sum = 0;
		for (int i = 0; i < n; ++i)
			sum += (i + 1) * (long long)v[i];
		cout << sum << endl;
	}
	return 0;
}
