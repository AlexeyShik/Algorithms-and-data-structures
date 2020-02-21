#include <iostream>
#include <vector>

using namespace std;

int main() {
	freopen("levenshtein.in", "r", stdin);
	freopen("levenshtein.out", "w", stdout);
	string s, t;
	getline(cin, s);
	getline(cin, t);
	s = ' ' + s;
	t = ' ' + t;
	vector <vector <int> > d(s.size() + 1, vector <int> (t.size() + 1));
	d[0][0] = 0;
	for (size_t i = 1; i <= s.size(); ++i)
		d[i][0] = i;
	for (size_t i = 1; i <= t.size(); ++i)
		d[0][i] = i;
	for (size_t i = 1; i <= s.size(); ++i)
		for (size_t j = 1; j <= t.size(); ++j) {
			int add = 0;
			if (s[i] != t[j])
				add = 1;
			d[i][j] = min(d[i - 1][j] + 1, d[i][j - 1] + 1);
			d[i][j] = min(d[i][j], d[i - 1][j - 1] + add);
		}
	cout << d[s.size()][t.size()];
	return 0;
}
