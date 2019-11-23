#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int *st = (int*)malloc(2 * sizeof(int));
    size_t sz = 0, next_sz = 4;
    string s;
    while (cin >> s) {
        bool number = s[0] >= '0' && s[0] <= '9';
        if (number) {
        	if (sz + 1 == next_sz) {
        		next_sz *= 2;
        		int *tmp = (int*)malloc(next_sz * sizeof(int));
        		for (int i = 0; i < (int)sz; ++i)
        			tmp[i] = st[i];
        		st = tmp;
			}
			int value = 0;
			for (char c : s) {
				value *= 10;
				value += (c - '0');
			}
			st[sz++] = value;
		} else {
			int b = st[--sz];
			int a = st[--sz];
			if (s == "+")
				a += b;
			if (s == "*")
				a *= b;
			if (s == "-")
				a -= b;
			st[sz++] = a;
		}
    }
    cout << st[0];
    return 0;
}
