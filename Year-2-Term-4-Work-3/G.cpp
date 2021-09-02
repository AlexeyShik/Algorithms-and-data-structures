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

vector<vector<int>> g, org;
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

void f(ll A, ll I) {
    if (A == 0) {
        color.clear();
        color.resize(g.size());
        if (color_2(I)) {
            for (int i = 0; i < (int) g.size(); ++i) {
                if ((I & (1ll << i)) != 0) {
                    cout << 1 << ' ';
                } else {
                    cout << (color[i] ? 2 : 3) << ' ';
                }
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

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    org.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
        org[u].push_back(v);
    }
    c.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int v : g[i]) {
            c[i] |= (1ll << v);
        }
    }
    f((1ll << n) - 1, 0ll);
}