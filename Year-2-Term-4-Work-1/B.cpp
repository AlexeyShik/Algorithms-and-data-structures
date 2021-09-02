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

vector<int> pref_func(string &s) {
    vector<int> pi(s.size(), 0);
    for (int i = 1; i < (int) s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    string t, p;
    cin >> p >> t;
    string s = p + "$" + t;
    vector<int> pi = pref_func(s);
    vector<int> ans;
    for (int i = (int) p.size() + 1; i < (int) s.size(); ++i) {
        if (pi[i] == (int) p.size()) {
            ans.push_back(i - 2 * p.size() + 1);
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) {
        cout << x << ' ';
    }
    return 0;
}
