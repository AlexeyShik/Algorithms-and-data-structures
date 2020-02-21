#include <bits/stdc++.h>

using namespace std;

vector <char> ans;

void lcs(string &s, string &t) {
	if (s.size() == 1) {
		bool check = false;
		for (char c : t)
			check |= (c == s[0]);
		if (check)
			ans.push_back(s[0]);
		return;
	}
	if (t.empty())
		return;
	int n = (int)s.size();
	int m = (int)t.size();
	string s1 = s.substr(0, n / 2);
	string s2 = s.substr(n / 2, n - 1);
	vector <int> dp1(m + 1, 0), prev(m + 1, 0);
	for (int i = 0; i < n / 2; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (s1[i] == t[j - 1])
				dp1[j] = (j > 0 ? prev[j - 1] : 0) + 1;
			dp1[j] = max(dp1[j], max(prev[j], j > 0 ? dp1[j - 1] : 0));
		}
		swap(dp1, prev);
		dp1.assign(m + 1, 0);
	}
	swap(dp1, prev);
	reverse(s2.begin(), s2.end());
	reverse(t.begin(), t.end());
	vector <int> dp2(m + 1, 0);
	prev.resize(m + 1, 0);
	for (int i = 0; i < (int)s2.size(); ++i) {
		for (int j = 1; j <= m; ++j) {
			if (s2[i] == t[j - 1])
				dp2[j] = (j > 0 ? prev[j - 1] : 0) + 1;
			dp2[j] = max(dp2[j], max(prev[j], j > 0 ? dp2[j - 1] : 0));
		}
		swap(dp2, prev);
		dp2.assign(m + 1, 0);
	}
	swap(dp2, prev);
	reverse(dp2.begin(), dp2.end());
	int mx = -1, mj = 0;
	for (int j = 0; j <= m; ++j)
		if (dp1[j] + dp2[j] > mx) {
			mx = dp1[j] + dp2[j];
			mj = j;
		}
	reverse(t.begin(), t.end());
	reverse(s2.begin(), s2.end());
	string t1 = t.substr(0, mj);
	string t2 = t.substr(mj, m);
	lcs(s1, t1);
	lcs(s2, t2);
}

int main() {
	string a, b;
	cin >> a >> b;
	lcs(a, b);
	for (char c : ans)
		cout << c;
    return 0;
}
