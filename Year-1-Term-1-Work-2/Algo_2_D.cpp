#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

int main() {
	int n;
	const ld eps = 1e-8;
	ld a;
	cin >> n >> a;
	ld l = 0, r = a, ans = -1;
	while (r - l > eps) {
		ld m = (l + r) / 2;
		ld prev = a, curr = m;
		bool optimum = true;
		for (int i = 1; i < n - 1; ++i) {
			ld next = 2 * curr - prev + 2;
			prev = curr;
			curr = next;
			optimum &= (next > 0);
		}
		if (optimum) {
			r = m;
			ans = curr;
		}
		else
			l = m;
	}
	printf("%.2lf", (double)ans);
	return 0;
}
