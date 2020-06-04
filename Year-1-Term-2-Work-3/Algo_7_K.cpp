#include <iostream>
#include <vector>
#include <unordered_map>

#pragma GCC optimize("O3")

using namespace std;

unordered_map <int, int> dsu, rg, lca;
unordered_map <int, bool> used;
unordered_map <int, vector <int> > g;
unordered_map <int, vector <pair <int, int> > > qs;
vector <int> ans;

int get(int i) {
    return dsu[i] = (i == dsu[i] ? i : get(dsu[i]));
}

void make_union(int u, int v, int l) {
    u = get(u);
    v = get(v);
    if (u == v) {
        return;
    }
    if (rg[u] > rg[v]) {
        swap(u, v);
    }
    dsu[u] = v;
    lca[v] = l;
    rg[v]++;
}

void dfs(int u) {
    used[u] = true;
    dsu[u] = u;
    lca[u] = u;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs(v);
            make_union(u, v, u);
        }
    }
    for (auto q : qs[u]) {
        if (used[q.first]) {
            ans[q.second] = lca[get(q.first)];
        }
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        u--, v--;
        if (s[0] == 'G') {
            qs[u].push_back({v, i});
            qs[v].push_back({u, i});
        } else {
            g[u].push_back(v);
        }
    }
    ans.resize(n, -1);
    dfs(0);
    for (int i = 0; i < n; ++i) {
        if (ans[i] != -1) {
            cout << ans[i] + 1 << endl;
        }
    }
    return 0;
}
