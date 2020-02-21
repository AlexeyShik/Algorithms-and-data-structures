#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
vector <vector <pair <int, int> > > ans;
int cnt = 0, n;

int main() {
    int n = -1;
    while (n != 0) {
    	cin >> n;
    	if (n == 0)
    		break;
    	vector <int> v(n);
    	for (int i = 0; i < n; ++i)
    		cin >> v[i];
    	bool check = true;
    	for (int i = 1; i < n; ++i)
    		check &= (v[i - 1] <= v[i]);
    	if (check) {
    		cout << -1 << endl;
    		continue;
		}
		int id = -1;
		for (int i = 0; i < n; ++i)
			if (v[i] == 1) {
				id = i;
				break;
			}
		vector <pair <int, int > > ans;
		for (int i = id + 1; i < n; ++i)
			if (v[i] == 1)
				ans.push_back({id, i});
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j < id; ++j)
				ans.push_back({j - 1, j});
			if (id - 1 >= 0 && id + 2 <= n)
				ans.push_back({id - 1, id + 1});
			for (int j = id + 2; j < n; ++j)
				ans.push_back({j - 1, j});
		}
		int k = 0;
		for (int i = 0; i < n; ++i)
			if (v[i] == 1)
				++k;
		int nid = n - k;
		for (int i = 1; i < nid; ++i)
			ans.push_back({i - 1, i});
		for (int i = nid - 1; i >= 1; --i)
			ans.push_back({i - 1, i});
		cout << ans.size() << endl;
		for (auto p : ans)
			cout << p.first + 1 << ' ' << p.second + 1 << endl;
	}
    return 0;
}
