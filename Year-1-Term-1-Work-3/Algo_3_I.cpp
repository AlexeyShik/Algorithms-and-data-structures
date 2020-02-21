#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	int n, m;
	cin >> n >> m;
	if (m <= 16) {
		for (int i = 0; i < m; ++i)
			cout << "0 1 1" << endl;
		return 0;
	}
	double f = sqrt((double)m * (double)log2(m)) / 4;
	int k = (int)f + ((int)f != f);
	int curr = k + 1;
	for (int i = 1; i < k + 1; ++i) {
		cout << "1 " << curr << " " << i << endl;
		--m;
	}
	for (int i = k + 2; i <= 2 * (k + 1); ++i) {
		cout << "1 " << i << " " << curr << endl;
		--m;
		for (int j = 1; j + 1 < k + 1; j += 2)  {
			cout << "0 " << j << " " << j + 1 << endl;
			--m;
		}
		curr = i;
	}
	while (m) {
		cout << "0 1 1" << endl;
		--m;
	}
	return 0;
}
