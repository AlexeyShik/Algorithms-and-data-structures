#include <iostream>
#include <vector>
#pragma GCC optimize("O3")

using namespace std;

const int inf = 1e9, maxn = 8e5 + 1;
int mod;

struct Matrix {
    int a00, a01, a10, a11;
    Matrix(int a00, int a01, int a10, int a11) : a00(a00), a01(a01), a10(a10), a11(a11) {}
    Matrix(Matrix const &b) = default;
    Matrix() : a00(1), a01(0), a10(0), a11(1) {}
};

Matrix operator* (const Matrix &a, const Matrix &b) {
    return Matrix((a.a00 * b.a00 + a.a01 * b.a10) % mod, (a.a00 * b.a01 + a.a01 * b.a11) % mod,
                  (a.a10 * b.a00 + a.a11 * b.a10) % mod, (a.a10 * b.a01 + a.a11 * b.a11) % mod);
}

istream &operator >> (istream &in, Matrix &m) {
    in >> m.a00 >> m.a01 >> m.a10 >> m.a11;
    return in;
}

ostream &operator << (ostream &out, const Matrix &m) {
    out << m.a00 << ' ' << m.a01 << endl << m.a10 << ' ' << m.a11 << endl << endl;
    return out;
}

Matrix E = Matrix();
vector <Matrix> mul(maxn);
vector <Matrix> val(2e5);

inline void build(int id, int l, int r) {
    if (l == r - 1) {
        mul[id] = val[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * id + 1, l, m);
    build(2 * id + 2, m, r);
    mul[id] = mul[2 * id + 1] * mul[2 * id + 2];
}

inline Matrix query(int id, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r)
        return mul[id];
    if (qr <= l || ql >= r)
        return E;
    int m = (l + r) / 2;
    return query(2 * id + 1, l, m, ql, min(m, qr)) * query(2 * id + 2, m, r, max(ql, m), qr);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> mod >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }
    build(0, 0, n);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(0, 0, n, l - 1, r);
    }
    return 0;
}
