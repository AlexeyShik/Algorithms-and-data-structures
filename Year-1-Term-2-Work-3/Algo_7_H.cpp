#include <iostream>
#include <vector>
#pragma GCC optimize("O3")

using namespace std;

const int inf = 1e9, maxn = 1e5 + 1;

vector <int> nxt(4 * maxn, inf);
vector <bool> val(maxn, 0);

inline void pull(int id) {
    nxt[id] = (nxt[2 * id + 1] == inf ? nxt[2 * id + 2] : nxt[2 * id + 1]);
}

inline void build(int id, int l, int r) {
    if (l == r - 1) {
        nxt[id] = l;
        return;
    }
    int m = (l + r) / 2;
    build(2 * id + 1, l, m);
    build(2 * id + 2, m, r);
    pull(id);
}

inline void update(int id, int l, int r, int pos, int d) {
    if (l == pos && pos + 1 == r) {
        val[l] = d;
        nxt[id] = (d == 0 ? l : inf);
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) {
        update(2 * id + 1, l, m, pos, d);
    } else {
        update(2 * id + 2, m, r, pos, d);
    }
    pull(id);
}

inline int query(int id, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r)
        return nxt[id];
    if (qr <= l || ql >= r)
        return inf;
    int m = (l + r) / 2;
    int L = query(2 * id + 1, l, m, ql, min(m, qr));
    int R = query(2 * id + 2, m, r, max(ql, m), qr);
    return L == inf ? R : L;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    build(0, 0, n);
    while (q--) {
        string s;
        int pos;
        cin >> s >> pos;
        pos--;
        if (s.size() == 5) {
            int i = query(0, 0, n, pos, n);
            if (i == inf) {
                i = query(0, 0, n, 0, pos);
            }
            cout << i + 1 << endl;
            update(0, 0, n, i, 1);
        } else {
            update(0, 0, n, pos, 0);
        }
    }
    return 0;
}