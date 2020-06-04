#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
using namespace std;

const int inf = 1e9+7;

inline void dfs(const int &u, const int &p, vector <vector <int> > &g,
        vector <pair <int, int> > &order, vector <int> &to_order, vector <int> &d) {
    d[u] = (p == -1 ? 0 : d[p] + 1);
    to_order[u] = order.size();
    order.push_back({d[u], u});
    for (const int &v : g[u]) {
        if (v != p) {
            dfs(v, u, g, order, to_order, d);
            order.push_back({d[u], u});
        }
    }
}

inline int query(int l, int r, vector <vector <pair <int, int> > > &mini, vector <int> &log) {
    if (l > r) {
        swap(l, r);
    }
    int k = log[r - l + 1];
    return mini[l][k].first <= mini[r - (1 << k) + 1][k].first
    ? mini[l][k].second : mini[r - (1 << k) + 1][k].second;
}

inline void solve(int n) {
    vector <vector <int> > g(n);
    vector <pair <int, int> > order;
    vector <int> d(n, 0), to_order(n, -1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, -1, g, order, to_order, d);
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
    int q;
    cin >> q;
    int root = 0;
    while (q--) {
        char c;
        cin >> c;
        if (c == '!') {
            cin >> root;
            root = to_order[root - 1];
        } else {
            int l, r;
            cin >> l >> r;
            l = to_order[l - 1];
            r = to_order[r - 1];
            int t1 = query(l, r, mini, log);
            int t2 = query(root, l, mini, log);
            int t3 = query(root, r, mini, log);
            if (d[t1] > d[t2] && d[t1] > d[t3]) {
                cout << t1 + 1 << endl;
            } else if (d[t2] > d[t1] && d[t2] > d[t3]) {
                cout << t2 + 1 << endl;
            } else {
                cout << t3 + 1 << endl;
            }
        }
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            return 0;
        }
        solve(n);
    }
}
