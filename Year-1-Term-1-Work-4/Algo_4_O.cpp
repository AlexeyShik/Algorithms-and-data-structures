#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	int x, a, y, b, l;
	cin >> x >> a >> y >> b >> l;
	int lb = 0, rb = x * a + y * b + 1;
	while (rb - lb > 1) {
		int md = (lb + rb) / 2;
		vector <vector <int> > dp(x + 1, vector <int> (y + 1, 0));
		for (int i = 0; i <= x; ++i)
			for (int j = 0; j <= y; ++j)
				for (int s = 0; s <= i; ++s) {
					int t = max(0, (md - s * a + b - 1) / b);
					if (j - t < 0)
						continue;
					dp[i][j] = max(dp[i][j], dp[i - s][j - t] + 1);
				}
		if (dp[x][y] >= l)
			lb = md;
		else
			rb = md;
	}
	cout << lb;
	return 0;
}
