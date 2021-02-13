#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;

const ld inf = 1e12 + 7;

ld calc(pll &p1, pll &p2) {
    return sqrt(pow(p1.first - p2.first, 2)
                + pow(p1.second - p2.second, 2));
}

int main() {
    fastio;
    int n;
    cin >> n;
    vector<pll> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }
    vector<ld> min_in(n, inf);
    vector<bool> used(n, false);
    min_in[0] = 0;
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        ld min_val = inf;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && min_in[j] < min_val) {
                min_val = min_in[j];
                u = j;
            }
        }
        ans += min_val;
        used[u] = true;
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                ld w = calc(points[u], points[j]);
                min_in[j] = min(min_in[j], w);
            }
        }
    }
    cout << setprecision(20) << ans;
    return 0;
}
