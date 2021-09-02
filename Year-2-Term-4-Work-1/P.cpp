#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <unordered_set>
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

int main() {
    fastio;
    int n;
    ll m;
    cin >> n >> m;
    vector<ll> pi(n);
    for (int i = 1; i < n; ++i) {
        cin >> pi[i];
    }
    ll ans = m;
    ll left = n;
    for (int i = (int) n - 1; i >= 1; --i) {
        if (pi[i] == 0 && left > i) {
            int borders = 0;
            int j = i;
            while (j != 0 && pi[j - 1] != 0) {
                if (pi[(int) pi[j - 1]] == 0) {
                    ++borders;
                }
                j = (int) pi[j - 1];
            }
            ans *= m - borders - 1;
            ans %= mod;
        }
        left = min(left, i - pi[i] + 1);
    }
    cout << ans;
    return 0;
}
