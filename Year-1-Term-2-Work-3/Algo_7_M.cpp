#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
using namespace std;
typedef long long ll;

const int inf = 1e9+7;
vector <vector <int> > g;
vector <pair <int, int> > order;
vector <int> d, to_order;

void dfs(const int &u, const int &p = -1) {
    d[u] = (p == -1 ? 0 : d[p] + 1);
    to_order[u] = order.size();
    order.push_back({d[u], u});
    for (const int &v : g[u]) {
        dfs(v, u);
        order.push_back({d[u], u});
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    g.resize(n);
    to_order.resize(n, -1);
    d.resize(n, 0);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    dfs(0);
    int m = order.size();
    vector <int> log(m + 1, 0);
    for (int i = 2; i <= m; ++i) {
        log[i] = log[i / 2] + 1;
    }
    vector <vector <pair <int, int> > > mini(m, vector <pair <int, int> > (log[m] + 1, {inf, inf}));
    for (int i = 0; i < m; ++i) {
        mini[i][0] = order[i];
    }
    for (int k = 1; k <= log[m]; ++k) {
        for (int i = 0; i + (1 << (k - 1)) < m; ++i) {
            if (mini[i][k - 1].first <= mini[i + (1 << (k - 1))][k - 1].first) {
                mini[i][k] = mini[i][k - 1];
            } else {
                mini[i][k] = mini[i + (1 << (k - 1))][k - 1];
            }
        }
    }
    ll a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    ll ans = 0, curr = 0;
    while (q--) {
        int l = to_order[((int)a1 + (int)curr) % n], r = to_order[(int)a2];
        if (l > r) {
            swap(l, r);
        }
        int k = log[r - l + 1];
        if (mini[l][k].first <= mini[r - (1 << k) + 1][k].first) {
            curr = mini[l][k].second;
        } else {
            curr = mini[r - (1 << k) + 1][k].second;
        }
        ans += curr;
        ll a3 = (x * a1 + y * a2 + z) % n;
        ll a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3;
        a2 = a4;
    }
    cout << ans;
    return 0;
}
