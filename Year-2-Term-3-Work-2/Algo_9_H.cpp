#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;

const ll inf = 1e12 + 7;

struct edge {
    int from;
    int to;
    ll w;
};

bool cmp(edge &e1, edge &e2) {
    return e1.w < e2.w;
}

int get(int u, vector<int> &dsu) {
    return dsu[u] = (dsu[u] == u ? u : get(dsu[u], dsu));
}

void join(int u, int v, vector<int> &dsu, vector<int> &rank) {
    if (rank[u] > rank[v]) {
        swap(u, v);
    }
    dsu[v] = u;
}

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    vector<edge> g;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        g.push_back({u, v, w});
    }
    sort(g.begin(), g.end(), cmp);
    vector<int> dsu(n), rank(n, 0);
    for (int i = 0; i < n; ++i) {
        dsu[i] = i;
    }
    ll ans = 0;
    for (edge &e : g) {
        int u = e.from;
        int v = e.to;
        int u0 = get(u, dsu);
        int v0 = get(v, dsu);
        if (u0 == v0) {
            continue;
        }
        ans += e.w;
        join(u0, v0, dsu, rank);
    }
    cout << ans;
    return 0;
}
