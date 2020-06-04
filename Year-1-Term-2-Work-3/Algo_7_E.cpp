#include <iostream>

using namespace std;

const int inf = 1e9, maxn = 2e6 + 1;

long long sum[maxn], add[maxn], val[maxn];

inline void pull(int id) {
    sum[id] = sum[2 * id + 1] + sum[2 * id + 2];
}

inline void push(int id, int l, int r) {
    if (add[id] == inf) {
        return;
    }
    sum[id] = add[id] * (r - l);
    if (2 * id + 1 < maxn)
        add[2 * id + 1] = add[id];
    if (2 * id + 2 < maxn)
        add[2 * id + 2] = add[id];
    add[id] = inf;
}

void build(int id, int l, int r) {
    add[id] = inf;
    if (l == r - 1) {
        sum[id] = val[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * id + 1, l, m);
    build(2 * id + 2, m, r);
    pull(id);
}

void update(int id, int l, int r, int ql, int qr, int d) {
    push(id, l, r);
    if (ql <= l && qr >= r) {
        add[id] = d;
        push(id, l, r);
        return;
    }
    if (r <= ql || l >= qr)
        return;
    int m = (l + r) / 2;
    update(2 * id + 1, l, m, ql, qr, d);
    update(2 * id + 2, m, r, ql, qr, d);
    pull(id);
}

long long query(int id, int l, int r, int ql, int qr) {
    push(id, l, r);
    if (ql <= l && qr >= r)
        return sum[id];
    if (qr <= l || ql >= r)
        return 0;
    int m = (l + r) / 2;
    return query(2 * id + 1, l, m, ql, qr) + query(2 * id + 2, m, r, ql, qr);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> val[i];
    build(0, 0, n);
    string s;
    while (cin >> s) {
        if (s == "sum") {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n, l - 1, r) << endl;
        } else {
            int l, d;
            cin >> l >> d;
            update(0, 0, n, l - 1, l, d);
        }
    }
    return 0;
}
