#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <set>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int>> g;
vector<bool> color;
vector<ll> c;

bool color_2(ll closed) {
    color.clear();
    color.resize(g.size());
    vector<int> used(g.size(), 0);
    for (int i = 0; i < (int) g.size(); ++i) {
        if ((closed & (1ll << i)) != 0) {
            used[i] = 2;
        }
    }
    queue<int> mq;
    for (int i = 0; i < (int) g.size(); ++i) {
        if (used[i] == 0) {
            mq.push(i);
        }
    }
    queue<int> q;
    while (!mq.empty()) {
        int x = mq.front();
        mq.pop();
        if (used[x] == 0) {
            q.push(x);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (used[v] == 1) {
                    if (color[u] == color[v]) {
                        return false;
                    }
                } else if (used[v] == 0) {
                    color[v] = !color[u];
                    used[v] = 1;
                    q.push(v);
                }
            }
            used[u] = 2;
        }
    }
    return true;
}

vector<int> val_set(ll A) {
    ll B = A;
    vector<int> res;
    while (B != 0) {
        ll allm1 = B & (B - 1);
        res.push_back((int) log2(B - (B & allm1)));
        B = allm1;
    }
    return res;
}

int get_color(int i, ll I) {
    if ((I & (1ll << i)) != 0) {
        return 1;
    } else {
        return (color[i] ? 2 : 3);
    }
}

void f(ll A, ll I) {
    if (A == 0) {
        color.clear();
        color.resize(g.size());
        if (color_2(I)) {
            for (int i = 0; i < (int) g.size(); ++i) {
                for (int v : g[i]) {
                    if (get_color(i, I) == get_color(v, I)) {
                        return;
                    }
                }
            }
            cout << "YES" << endl;
            for (int i = 0; i < (int) g.size(); ++i) {
                cout << get_color(i, I) << ' ';
            }
            exit(0);
        }
        return;
    }
    int u = -1;
    int cnt = 1e9;
    for (int x : val_set(A)) {
        int cnt1 = (int) __builtin_popcount((unsigned int) (c[x] & A & ((1ll << 32) - 1)));
        cnt1 += (int) __builtin_popcount((unsigned int) ((c[x] & A) >> 32));
        if (cnt1 < cnt) {
            cnt = cnt1;
            u = x;
        }
    }
    A &= ~(1ll << u);
    vector<int> v1 = val_set(c[u] & A);
    for (int v : v1) {
        A &= ~(1ll << v);
    }
    I |= (1ll << u);
    f(A, I);
    I &= ~(1ll << u);
    for (int v : v1) {
        A |= (1ll << v);
    }
    A |= (1ll << u);

    for (int u0 : v1) {
        A &= ~(1ll << u0);
        vector<int> v2 = val_set(c[u0] & A);
        for (int v : v2) {
            A &= ~(1ll << v);
        }
        I |= (1ll << u0);
        f(A, I);
        I &= ~(1ll << u0);
        for (int v : v2) {
            A |= (1ll << v);
        }
        A |= (1ll << u0);
    }
}

vector<vector<pii>> _g;
vector<int> _color;
vector<int> _used;

bool _color_2() {
    _color.resize(g.size());
    _used.resize(g.size(), 0);
    queue<int> mq;
    for (int i = 0; i < (int) g.size(); ++i) {
        mq.push(i);
    }
    queue<int> q;
    while (!mq.empty()) {
        int x = mq.front();
        mq.pop();
        if (_used[x] == 0) {
            q.push(x);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (_used[v] == 1) {
                    if (_color[u] == _color[v]) {
                        return false;
                    }
                } else if (_used[v] == 0) {
                    _color[v] = !_color[u];
                    _used[v] = 1;
                    q.push(v);
                }
            }
            _used[u] = 2;
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    _g.resize(n);
    int max_d = 0;
    vector<int> deg(n, 0);
    vector<pii> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges.emplace_back(u, v);
        _g[u].push_back({v, i});
        _g[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
        max_d = max(deg[u], max_d);
        max_d = max(deg[v], max_d);
    }
    if (max_d == 0) {
        cout << "YES";
        return 0;
    }
    if (max_d == 1) {
        cout << "YES" << endl;
        for (int i = 0; i < m; ++i) {
            cout << 1 << ' ';
        }
        return 0;
    }
    if (max_d > 3) {
        cout << "NO";
        return 0;
    }
    g.resize(m);
    color.resize(m);
    c.resize(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            if (edges[i].first == edges[j].first || edges[i].first == edges[j].second
                || edges[i].second == edges[j].first || edges[i].second == edges[j].second) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    if (max_d == 2 && _color_2()) {
        cout << "YES" << endl;
        for (int col : _color) {
            cout << col + 1 << ' ';
        }
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        for (int v : g[i]) {
            c[i] |= (1ll << v);
        }
    }
    f((1ll << m) - 1, 0ll);
    cout << "NO";
    return 0;
}