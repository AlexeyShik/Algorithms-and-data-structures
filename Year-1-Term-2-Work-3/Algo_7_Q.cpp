#include <iostream>
#include <vector>
#include <unordered_map>
#pragma GCC optimize("O3")

using namespace std;
const long long inf = 1e18;

vector <vector <int> > g;
vector <int> sz, leader, par, heaviest, dist;

struct segment_tree {
    int n;
    vector <long long> val, keys, maxv;
    unordered_map <int, int> compress;
    segment_tree() :  n(0), val(0), keys(0), maxv(0) {}

    void insert(int x) {
        val.push_back(0);
        keys.push_back(x);
    }

    void build() {
        n = val.size();
        maxv.resize(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            compress[(int)keys[i]] = i;
        }
    }

    void pull(int id) {
        maxv[id] = max(maxv[2 * id + 1], maxv[2 * id + 2]);
    }


    void update(int id, int l, int r, int k, long long d) {
        if (l + 1 == r && l == k) {
            maxv[id] += d;
            return;
        }
        if (r <= k || k < l) {
            return;
        }
        int m = (l + r) / 2;
        update(2 * id + 1, l, m, k, d);
        update(2 * id + 2, m, r, k, d);
        pull(id);
    }

    void update(int u, long long d) {
        update(0, 0, n, compress[u], d);
    }

    long long query(int id, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return maxv[id];
        }
        if (qr <= l || r <= ql) {
            return -inf;
        }
        int m = (l + r) / 2;
        return max(query(2 * id + 1, l, m, ql, qr), query(2 * id + 2, m, r, ql, qr));
    }

    long long query(int u, int v) {
        u = compress[u];
        v = compress[v];
        if (u > v) {
            swap(u, v);
        }
        return query(0, 0, n, u, v + 1);
    }
};

vector <segment_tree*> tree;

void calc_sz(int u, int p = -1) {
    par[u] = (p == -1 ? u : p);
    if (p != -1) {
        dist[u] = dist[p] + 1;
    }
    int max_sz = 0;
    for (int v : g[u]) {
        if (v != p) {
            calc_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                heaviest[u] = v;
            }
        }
    }
}

void dfs(int u, int p = -1) {
    if (p == -1) {
        tree[leader[u]]->insert(u);
    }
    for (int v : g[u]) {
        if (v != p) {
            if (heaviest[u] == v) {
                leader[v] = leader[u];
            }
            tree[leader[v]]->insert(v);
            dfs(v, u);
        }
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n;
    g.resize(n);
    sz.resize(n, 1);
    leader.resize(n);
    tree.resize(n);
    par.resize(n);
    heaviest.resize(n, -1);
    dist.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        tree[i] = new segment_tree();
    }
    for (int i = 0; i < n; ++i) {
        leader[i] = i;
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    calc_sz(0);
    dfs(0);
    for (int i = 0; i < n; ++i) {
        tree[i]->build();
    }
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == 'G') {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int lu = leader[u], lv = leader[v];
            long long ans = -inf;
            while (lu != lv) {
                if (dist[lu] > dist[lv]) {
                    ans = max(ans, tree[lu]->query(lu, u));
                    u = par[lu];
                    lu = leader[u];
                } else {
                    ans = max(ans, tree[lv]->query(lv, v));
                    v = par[lv];
                    lv = leader[v];
                }
            }
            ans = max(ans, tree[lu]->query(u, v));
            cout << ans << endl;
        } else {
            int v;
            long long d;
            cin >> v >> d;
            v--;
            tree[leader[v]]->update(v, d);
        }
    }
    return 0;
}
