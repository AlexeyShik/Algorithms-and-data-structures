#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)

using namespace std;
const int mod = 65536;

int phi(int n) {
	int ans = n;
	for (int i = 2; i * i <= n; ++i)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			ans -= ans / i;
		}
	if (n > 1)
		ans -= ans / n;
	return ans;
}

const int times = phi(mod);

int p(int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return int((1ll * a * p(a, n - 1)) % mod);
	int b = p(a, n / 2) % mod;
	return int(((1ll * b * b)) % mod);
}

int main() {
	int* r[26];
	int rsz[26];
	for (int i = 0; i < 26; ++i)
		rsz[i] = 2;
	int realsz[26];
	for (int i = 0; i < 26; ++i)
		realsz[i] = 0;
	for (int i = 0; i < 26; ++i)
		r[i] = (int*)malloc(2 * sizeof(int));
	size_t sz = 0, next_sz = 2, beg = 0;
	int *q = (int*)malloc(sizeof(int));
	map <string, size_t> label;
	size_t curr = 0, time = 0;
	char** str = (char**)malloc(2 * sizeof(char*));
	size_t strsz = 0, next_str_sz = 2;
	int *lens = (int*)malloc(2 * sizeof(int));
	string s;
	while (cin >> s) {
		if (strsz + 1 >= next_str_sz) {
			char ** tmp = (char**)malloc(2 * next_str_sz * sizeof(char*));
			int* lmp = (int*)malloc(2 * next_str_sz * sizeof(int));
			for (size_t i = 0; i < strsz; ++i) {
				lmp[i] = lens[i];
				tmp[i] = str[i];
			}
			swap(lmp, lens);
			swap(tmp, str);
			next_str_sz *= 2;
		}
		if (s[0] == ':') {
            string t;
            t.resize(s.size() - 1);
            for (size_t i = 0; i < s.size() - 1; ++i)
                t[i] = s[i + 1];
            label[t] = strsz;
        }
		str[strsz] = (char*)malloc(s.size() * sizeof(char));
		for (size_t i = 0; i < s.size(); ++i)
			str[strsz][i] = s[i];
		lens[strsz] = (int)s.size();
		strsz++;
	}
	while (curr < strsz) {
		char *p = (char*)malloc(lens[curr] * sizeof(char));
		for (int i = 0; i < lens[curr]; ++i)
			p[i] = str[curr][i];
		if (curr >= time) {
			++curr;
			time = max(curr, time);
		} else {
			++curr;
		}
		if (sz + 1 == next_sz) {
			next_sz *= 2;
			int *tmp = (int*)malloc(next_sz * sizeof(int));
			for (size_t j = 0; j < sz; ++j)
				tmp[j] = q[j];
			swap(tmp, q);
		}
		if (p[0] == '+') {
			q[sz++] = (q[beg] + q[beg + 1]) % mod;
			beg += 2;
		}
		else
		if (p[0] == '-') {
			q[sz++] = (q[beg] - q[beg + 1] + mod) % mod;
			beg += 2;
		}
		else
		if (p[0] == '*') {
			q[sz++] = int((1ll * q[beg] * q[beg + 1]) % mod);
			beg += 2;
		}
		else
		if (p[0] == '/') {
			if (q[beg + 1] == 0) {
				q[sz] = 0;
			} else {
				// q[sz] = int((1ll * q[beg] * p(q[beg + 1], times - 1)) % mod);
				q[sz] = q[beg] / q[beg + 1];
				beg += 2;
			}
			sz++;
		}
		else
		if (p[0] == '%') {
			if (q[beg + 1] == 0) {
				q[sz] = 0;
			} else {
				q[sz] = q[beg] % q[beg + 1];
				beg += 2;
			}
			sz++;
		}
		else
		if (p[0] == '>') {
			int id = p[1] - 'a';
			if (realsz[id] + 1 >= rsz[id]) {
				rsz[id] *= 2;
				int *tmp = (int*)malloc(rsz[id] * sizeof(int));
				for (int j = 0; j < realsz[id]; ++j)
					tmp[j] = r[id][j];
				swap(r[id], tmp);
			}
			r[id][realsz[id]++] = q[beg++];
		}
		else
		if (p[0] == '<') {
			int id = p[1] - 'a';
			q[sz++] = r[id][realsz[id] - 1];
		}
		else
		if (p[0] == 'P' && lens[curr - 1] == 1) {
			cout << q[beg++] << endl;
		}
		else
		if (p[0] == 'P') {
			int id = p[1] - 'a';
			cout << r[id][realsz[id] - 1] << endl;
		}
		else
		if (p[0] == 'C' && lens[curr - 1] == 1) {
			cout << (char)(q[beg++] % 256);
		}
		else
		if (p[0] == 'C') {
			int id = p[1] - 'a';
			cout << (char)(r[id][realsz[id] - 1] % 256);
		}
		else
		if (p[0] == ':') {
			const string message = "Hello";
		}
		else
		if (p[0] == 'J') {
			string t;
			t.resize(lens[curr - 1] - 1);
			for (size_t i = 0; i < t.size(); ++i)
				t[i] = p[i + 1];
			curr = label[t];
		}
		else
		if (p[0] == 'Z') {
			int id = p[1] - 'a';
			string t;
			t.resize(lens[curr - 1] - 2);
			for (size_t i = 0; i < t.size(); ++i)
				t[i] = p[i + 2];
			if (r[id][realsz[id] - 1] == 0)
				curr = label[t];
		}
		else
		if (p[0] == 'E') {
			int id1 = p[1] - 'a';
			int id2 = p[2] - 'a';
			string t;
			t.resize(lens[curr - 1] - 3);
			for (size_t i = 0; i < t.size(); ++i)
				t[i] = p[i + 3];
			if (r[id1][realsz[id1] - 1] == r[id2][realsz[id2] - 1])
				curr = label[t];
		}
		else
		if (p[0] == 'G') {
			int id1 = p[1] - 'a';
			int id2 = p[2] - 'a';
			string t;
			t.resize(lens[curr - 1]);
			for (size_t i = 0; i < t.size(); ++i)
				t[i] = p[i + 3];
			if (r[id1][realsz[id1] - 1] > r[id2][realsz[id2] - 1])
				curr = label[t];
		}
		else
		if (p[0] == 'Q') {
			return 0;
		} else {
			int new_val = 0;
			for (size_t j = 0; j < (size_t)lens[curr - 1]; ++j)
				new_val = new_val * 10 + (p[j] - '0');
			q[sz++] = new_val;
		}
	}
	free(q);
	for (int i = 0; i < 26; ++i) {
		free(r[i]);
	}
	return 0;
}
/*
100
0
:start
>a
Zaend
<a
<a
1
+
-
>b
<b
Jstart
:end
P
*/
