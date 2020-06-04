#include <iostream>
#include <vector>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
const ll inf = 1e18, maxn = 1e5 + 1;

vector <ll> val(maxn, 0), pro(4 * maxn, 0), mini(4 * maxn, 0), type(4 * maxn, 0);

inline void pull(int id) {
    mini[id] = min(mini[2 * id + 1], mini[2 * id + 2]);
}

inline void relax(int id, int child) {
    if (type[child] == 0) {
        pro[child] = pro[id];
        type[child] = type[id];
    } else if (type[child] == 1 && type[id] == 1) {
        pro[child] += pro[id];
        type[child] = 1;
    } else if (type[child] == 1 && type[id] == 2) {
        pro[child] = pro[id];
        type[child] = 2;
    } else if (type[child] == 2 && type[id] == 1) {
        pro[child] += pro[id];
        type[child] = 2;
    } else if (type[child] == 2 && type[id] == 2) {
        pro[child] = pro[id];
        type[child] = 2;
    }
}

inline void propogate(int id) {
    if (2 * id + 1 < 4 * maxn) {
        relax(id, 2 * id + 1);
    }
    if (2 * id + 2 < 4 * maxn) {
        relax(id, 2 * id + 2);
    }
    pro[id] = type[id] = 0;
}

inline void push(int id) {
    if (type[id] == 0) {
        return;
    } else if (type[id] == 1) {
        mini[id] += pro[id];
    } else {
        mini[id] = pro[id];
    }
    if (type[id] != 0) {
        propogate(id);
    }
}

inline void build(int id, int l, int r) {
    if (l == r - 1) {
        mini[id] = val[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * id + 1, l, m);
    build(2 * id + 2, m, r);
    pull(id);
}

inline void update(int id, int l, int r, int ql, int qr, int d, int t) {
    push(id);
    if (ql <= l && qr >= r) {
        pro[id] = d;
        type[id] = t;
        push(id);
        return;
    }
    if (qr <= l || ql >= r)
        return;
    int m = (l + r) / 2;
    update(2 * id + 1, l, m, ql, qr, d, t);
    update(2 * id + 2, m, r, ql, qr, d, t);
    pull(id);
}

inline ll query(int id, int l, int r, int ql, int qr) {
    push(id);
    if (ql <= l && qr >= r)
        return mini[id];
    if (qr <= l || ql >= r)
        return inf;
    int m = (l + r) / 2;
    return min(query(2 * id + 1, l, m, ql, min(m, qr)), query(2 * id + 2, m, r, max(ql, m), qr));
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }
    build(0, 0, n);
    string s;
    while (cin >> s) {
        int l, r;
        cin >> l >> r;
        if (s[0] == 'm') {
            cout << query(0, 0, n, l - 1, r) << endl;
        } else {
            int x;
            cin >> x;
            int t = (s[0] == 'a' ? 1 : 2);
            update(0, 0, n, l - 1, r, x, t);
        }
    }
    return 0;
}
