#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define List pair <int, int>
#define val first
#define minim second
using namespace std;

int main() {
	fastio;
	int n, m, k;
	cin >> n >> m >> k;
	int sz1 = 0, sz2 = 0, next1 = 2, next2 = 2;
	List *st1 = (List*)malloc(next1 * sizeof(List));
	List *st2 = (List*)malloc(next2 * sizeof(List));
	int a, b, c, l1 = 0, l2 = 0;
	cin >> a >> b >> c;
	long long sum = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		if (i < k) {
			cin >> x;
		} else {
			x = (a * l2 + b * l1 + c);
		}
		l2 = l1;
		l1 = x;
		st1[sz1].val = x;
		st1[sz1].minim = sz1 != 0 ? min(x, st1[sz1 - 1].minim) : x;
		sz1++;
		if (sz1 >= next1) {
			next1 *= 2;
			st1 = (List*)realloc(st1, next1 * sizeof(List));
		}
		if (i + 1 >= m) {
			if (sz2 == 0) {
				while (sz1 != 0) {
					if (sz2 >= next2) {
						next2 *= 2;
						st2 = (List*)realloc(st2, next2 * sizeof(List));
					}
					st2[sz2].val = st1[sz1 - 1].val;
					st2[sz2].minim = (sz2 != 0 ? min(st2[sz2].val, st2[sz2 - 1].minim) : st2[sz2].val);
					sz2++;
					sz1--;
				}
			}
			long long ans = (sz1 == 0 ? st2[sz2 - 1].minim : st1[sz1 - 1].minim);
			if (sz1 != 0 && sz2 != 0) {
				ans = min(st1[sz1 - 1].minim, st2[sz2 - 1].minim);
			}
			sum = (long long)ans + sum;
			sz2--;
		}
	}
	free(st1);
	free(st2);
	cout << sum;
	return 0;
}


/*1000000 15 5
283471207 23947205 3
17625384 939393931 1838388 912740247 290470294*/
