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

int main() {
    string s, t;
    cin >> t >> s;
    vector<int> ans;
    for (int i = 0; i + (int) t.size() <= (int) s.size(); ++i) {
        bool ok = true;
        for (int j = 0; j < (int) t.size(); ++j) {
            ok &= s[i + j] == t[j];
        }
        if (ok) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) {
        cout << x << ' ';
    }
    return 0;
}
