#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
vector <vector <pair <int, int> > > ans;
int cnt = 0, n;

bool is2k(int x) {
	return (x & (x - 1)) == 0;
}

int bitonicSort(int l, int r, int k) {
	if (l + 1 == r)
		return k;
	int m = (l + r) / 2;
	for (int i = 0; i + l < m; ++i)
		if (m + i + 1 <= n) {
			ans[k].push_back({l + i + 1, m + i + 1});
			cnt++;
		}
	int ck = max(bitonicSort(l, m, k + 1), bitonicSort(m, r, k + 1));
	return ck;
}

int mergeBuild(int l, int r, int k) {
	if (l + 1 == r)
		return k;
	int m = (l + r) / 2;
	for (int i = 0; i + l < m; ++i)
		if (r - i <= n) {
			ans[k].push_back({l + i + 1, r - i});
			cnt++;
		}
	int ck = max(bitonicSort(l, m, k + 1), bitonicSort(m, r, k + 1));
	return ck;
}

int main() {
    cin >> n;
    ans.resize(20);
    int comp = 0;
    for (int i = 0; i + 2 <= n; i += 2) {
    	ans[0].push_back({i + 1, i + 2});
    	cnt++;
    }	
    mergeBuild(0, 4, 1);
    mergeBuild(4, 8, 1);
    mergeBuild(8, 12, 1);
    int k = mergeBuild(12, 16, 1);
    mergeBuild(0, 8, k);
    k = mergeBuild(8, 16, k);
    mergeBuild(0, 16, k);
    comp = 0;
    for (int i = 0; i < 20; ++i) {
    	if (ans[i].size() != 0) {
    		comp++;
    	}
    }
    cout << n << ' ' << cnt << ' ' << comp << endl;
    for (int i = 0; i < 20; ++i)
		if (ans[i].size() != 0) {
    		cout << ans[i].size() << ' ';
    		for (auto x : ans[i])
    			cout << x.first << ' ' << x.second << ' ';
    		cout << endl;
		}
    return 0;
}
