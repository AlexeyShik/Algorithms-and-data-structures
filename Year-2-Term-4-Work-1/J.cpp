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
const ll mod = 1e9 + 7;
const ll inf = 1e17;

vector<int> z_func(string &s) {
    vector<int> z(s.size(), 0);
    int l = 0, r = 0;
    for (int i = 1; i < (int) s.size(); ++i) {
        z[i] = 0;
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    fastio;
    string s, t;
    cin >> s;
    ll ans = 0;
    for (char c : s) {
        t = c + t;
        vector<int> z = z_func(t);
        int mx = 0;
        for (int x : z) {
            mx = max(mx, x);
        }
        ans += t.size() - mx;
        cout << ans << endl;
    }
    return 0;
}
