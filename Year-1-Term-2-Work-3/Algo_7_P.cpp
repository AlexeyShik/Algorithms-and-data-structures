#include <iostream>
#include <vector>
#include <unordered_map>
#pragma GCC optimize("O3")

using namespace std;

vector <vector <int> > g;
vector <int> sz, leader, par, heaviest, dist;

struct segment_tree {
    int n;
    vector <long long> val, keys, add;
    unordered_map <int, int> compress;
    segment_tree() :  n(0), val(0), keys(0), add(0) {}

    void insert(int x) {
        val.push_back(0);
        keys.push_back(x);
    }

    void build() {
        n = val.size();
        add.resize(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            compress[(int)keys[i]] = i;
        }
    }

    void propogate(int id, int child) {
        if (child < 4 * n) {
            add[child] += add[id];
        }
    }

    void push(int id, int l, int r) {
        if (l + 1 == r) {
            val[l] += add[id];
        }
        propogate(id, 2 * id + 1);
        propogate(id, 2 * id + 2);
        add[id] = 0;
    }

    void update(int id, int l, int r, int ql, int qr, long long d) {
        push(id, l, r);
        if (ql <= l && r <= qr) {
            add[id] += d;
            push(id, l, r);
            return;
        }
        if (r <= ql || qr <= l) {
            return;
        }
        int m = (l + r) / 2;
        update(2 * id + 1, l, m, ql, qr, d);
        update(2 * id + 2, m, r, ql, qr, d);
    }

    void update(int u, int v, long long d) {
        u = compress[u];
        v = compress[v];
        if (u > v) {
            swap(u, v);
        }
        update(0, 0, n, u, v + 1, d);
    }

    long long query(int id, int l, int r, int k) {
        push(id, l, r);
        if (l + 1 == r && l == k) {
            return val[l];
        }
        if (k < l || r <= k) {
            return 0;
        }
        int m = (l + r) / 2;
        return query(2 * id + 1, l, m, k) + query(2 * id + 2, m, r, k);
    }

    long long query(int u) {
        return query(0, 0, n, compress[u]);
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
        if (c == '+') {
            int u, v;
            long long d;
            cin >> u >> v >> d;
            u--, v--;
            int lu = leader[u], lv = leader[v];
            while (lu != lv) {
                if (dist[lu] > dist[lv]) {
                    tree[lu]->update(lu, u, d);
                    u = par[lu];
                    lu = leader[u];
                } else {
                    tree[lv]->update(lv, v, d);
                    v = par[lv];
                    lv = leader[v];
                }
            }
            tree[lu]->update(u, v, d);
        } else {
            int v;
            cin >> v;
            v--;
            cout << tree[leader[v]]->query(v) << endl;
        }
    }
    return 0;
}
