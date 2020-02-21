#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 7;

int need;
vector <vector <pii> > g;
vector <int> sz, ch;
vector <vector <int> > f;

void sizes(int u, int p) {
    sz[u] = 1;
    for (pii v : g[u]) {
        if (v.first != p) {
            sizes(v.first, u);
            sz[u] += sz[v.first];
            ch[u]++;
        }
    }
}

void dfs(int u, int p) {
    for (pii v : g[u]) {
        if (v.first != p) {
            dfs(v.first, u);
        }
    }
    vector <int> dp(need + 1, inf);
    dp[1] = 0;
    for (pii pp : g[u]) {
        int v = pp.first;
        if (v == p)
            continue;
        for (int k = need; k > 0; --k) {
            int t = dp[k] + 1;
            for (int s = 1; s <= sz[v]; ++s) {
                if (k - s > 0) {
                    t = min(t, dp[k - s] + f[v][s]);
                }
            }
            dp[k] = t;
        }
    }
    for (int k = 0; k <= need; ++k) {
        f[u][k] = dp[k];
    }
}

vector <int> rec(int u, int p, int t) {
    if (t == 0) {
        for (pii v : g[u]) {
            if (v.first == p) {
                vector <int> c(1, v.second);
                return c;
            }
        }
    }
    vector <vector <int> > dp(ch[u] + 1, vector <int> (t + 1, inf));
    vector <vector <int> > par(ch[u] + 1, vector <int> (t + 1, -1));
    vector <int> c(ch[u] + 1);
    dp[0][1] = 0;
    int j = 1;
    for (pii pp : g[u]) {
        int v = pp.first;
        if (v == p)
            continue;
        c[j] = v;
        for (int k = t; k > 0; --k) {
            dp[j][k] = dp[j - 1][k] + 1;
            par[j][k] = k;
            for (int s = 1; s <= sz[v]; ++s) {
                if (k - s > 0 && dp[j][k] > dp[j - 1][k - s] + f[v][s]) {
                    dp[j][k] = dp[j - 1][k - s] + f[v][s];
                    par[j][k] = k - s;
                }
            }
        }
        ++j;
    }
    j--;
    vector <int> ans;
    while (par[j][t] != -1) {
        int prev = par[j][t];
        int rem = t - prev;
        auto ch_ans = rec(c[j], u, rem);
        for (auto x : ch_ans)
            ans.push_back(x);
        t = prev;
        j--;
    }
    return ans;
}

int main() {
	srand(time(nullptr));
    int n, p;
    cin >> n >> p;
    need = p;
    g.resize(n);
    vector <int> pows(n, 0);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        pows[u]++;
    }
    int root = -1;
    for (int i = 0; i < n; ++i) {
        if (pows[i] == 0) {
            root = i;
        }
    }
    sz.resize(n, 0);
    ch.resize(n, 0);
    sizes(root, -1);
    f.resize(n, vector <int> (n + 1, inf));
    dfs(root, -1);
    cout << f[root][need] << endl;
    vector <int> ans = rec(root, -1, need);
    sort(ans.begin(), ans.end());
    for (int x : ans) {
        cout << x << ' ';
    }
    return 0;
}
