#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <cassert>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), \
cout.tie(0), cout.precision(20), cout.setf(ios::fixed)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9+7;
const ll inf = 1e17;

int max_pref_func(string &s) {
    vector<int> pi(s.size(), 0);
    int mx = 0;
    for (int i = 1; i < (int) s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
        mx = max(mx, pi[i]);
    }
    return mx;
}

int main() {
    string s;
    cin >> s;
    vector<vector<int>> f(s.size(), vector<int>(s.size(), 0));
    f[0][0] = 1;
    for (int j = 1; j < (int) s.size(); ++j) {
        string tmp = s.substr(0, j + 1);
        reverse(tmp.begin(), tmp.end());
        f[0][j] = f[0][j - 1] + (j + 1 - max_pref_func(tmp));
    }
    for (int i = 1; i < (int) s.size(); ++i) {
        int mx = 0;
        string tmp = s.substr(i - 1, s.size());
        vector<int> pi(tmp.size(), 0);
        for (int j = i; j < (int) s.size(); ++j) {
            int len = j - i + 1;
            int k = pi[len - 1];
            while (k > 0 && tmp[k] != tmp[len]) {
                k = pi[k - 1];
            }
            if (tmp[k] == tmp[len]) {
                ++k;
            }
            pi[len] = k;
            mx = max(mx, pi[len]);
            f[i][j] = f[i - 1][j] - (len + 1 - mx);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << f[l - 1][r - 1] << endl;
    }
    return 0;
}
