#include <iostream>
#include <vector>

using namespace std;

vector <vector <int> > g;
vector <int> sz;
int bunker = -1;

inline void dfs(const int &v, int p = -1) {
    sz[v] = 1;
    for (const int &u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
        }
    }
    if (g[v].size() == 2 && sz[v] - 1 == (int)g.size() - sz[v]) {
        bunker = v;
    }
}

const long long mod = 1e9+7;
const long long b = 1298119;
const long long a = 1057037;

long long tree_hash(int v, int p = -1) {
    long long hash = (1ll * g[v].size() * a) % mod;
    for (const auto &u : g[v]) {
        if (u != p) {
            hash = ((1ll * hash * b) % mod + 1ll * tree_hash(u, v)) % mod;
        }
    }
    return hash;
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    int root = 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sz.resize(n, 0);
    dfs(root);
    if (g[root].size() == 2 && sz[g[root][0]] == sz[g[root][1]]) {
        bunker = root;
    }
    if (bunker == -1 || g[bunker].size() != 2) {
        cout << "NO";
        return 0;
    }
    long long a = tree_hash(g[bunker][0], bunker);
    long long b = tree_hash(g[bunker][1], bunker);
    cout << ((a == b) ? "YES" : "NO");
    return 0;
}
