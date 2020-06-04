#include <iostream>
#include <vector>
#pragma GCC optimize("O3")

using namespace std;
typedef unsigned int uint;
int ni, nj, nh;

inline int f(int i) {
    return i & (i + 1);
}

inline int g(int i) {
    return i | (i + 1);
}

vector <vector <vector <uint> > > f123, f12, f13, f23, f1, f2, f3, f0;

void add(int l1, int l2, int l3, uint x) {
    for (int i = l1; i <= ni; i = g(i)) {
        for (int j = l2; j <= nj; j = g(j)) {
            for (int h = l3; h <= nh; h = g(h)) {
                f123[i][j][h] += x;
                f12[i][j][h] += (1 - l3) * x;
                f13[i][j][h] += (1 - l2) * x;
                f23[i][j][h] += (1 - l1) * x;
                f1[i][j][h] += (1 - l2) * (1 - l3) * x;
                f2[i][j][h] += (1 - l1) * (1 - l3) * x;
                f3[i][j][h] += (1 - l1) * (1 - l2) * x;
                f0[i][j][h] += (1 - l1) * (1 - l2) * (1 - l3) * x;
            }
        }
    }
}

void update(int l1, int l2, int l3, int r1, int r2, int r3, uint x) {
    add(l1, l2, l3, x);
    add(r1, l2, l3, -x);
    add(l1, r2, l3, -x);
    add(l1, l2, r3, -x);
    add(r1, r2, l3, x);
    add(r1, l2, r3, x);
    add(l1, r2, r3, x);
    add(r1, r2, r3, -x);
}

uint sum(int l1, int l2, int l3) {
    uint t123 = 0, t12 = 0, t13 = 0, t23 = 0, t1 = 0, t2 = 0, t3 = 0, t0 = 0;
    for (int i = l1; i >= 0; i = f(i) - 1) {
        for (int j = l2; j >= 0; j = f(j) - 1) {
            for (int h = l3; h >= 0; h = f(h) - 1) {
                t123 += f123[i][j][h];
                t12 += f12[i][j][h];
                t13 += f13[i][j][h];
                t23 += f23[i][j][h];
                t1 += f1[i][j][h];
                t2 += f2[i][j][h];
                t3 += f3[i][j][h];
                t0 += f0[i][j][h];
            }
        }
    }
    return t123 * l1 * l2 * l3 + t12 * l1 * l2 + t13 * l1 * l3 + t23 * l2 * l3
    + t1 * l1 + t2 * l2 + t3 * l3 + t0;
}

uint query(int l1, int l2, int l3, int r1, int r2, int r3) {
    return sum(r1 - 1, r2 - 1, r3 - 1)
           - sum(l1 - 1, r2 - 1, r3 - 1) - sum(r1 - 1, l2 - 1, r3 - 1)-sum(r1 - 1, r2 - 1, l3 - 1)
           + sum(l1 - 1, l2 - 1, r3 - 1) + sum(l1 - 1, r2 - 1, l3 - 1)+sum(r1 - 1, l2 - 1, l3 - 1)
           - sum(l1 - 1, l2 - 1, l3 - 1);
}

struct Triple {
    vector <int> a;
    Triple(int a1, int a2, int a3) {
        a.push_back(a1);
        a.push_back(a2);
        a.push_back(a3);
    }
    Triple() {
        a.resize(3, 0);
    }
};

struct Permutation {
    vector <int> to;
    Permutation() {
        to.resize(3, 0);
    }

    Triple make_perm(Triple t) {
        Triple nt = Triple();
        for (int i = 0; i < 3; ++i) {
            nt.a[to[i]] = t.a[i];
        }
        return nt;
    }
};

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> ni >> nj >> nh;
    Triple n = Triple(ni, nj, nh);
    Permutation perm = Permutation();
    if (ni <= nj && nj <= nh) {
        perm.to = {0, 1, 2};
    } else if (ni <= nh && nh <= nj) {
        perm.to = {0, 2, 1};
    } else if (nj <= ni && ni <= nh) {
        perm.to = {1, 0, 2};
    } else if (nj <= nh && nh <= ni) {
        perm.to = {2, 0, 1};
    } else if (nh <= ni && ni <= nj) {
        perm.to = {1, 2, 0};
    } else if (nh <= nj && nj <= ni) {
        perm.to = {2, 1, 0};
    }
    n = perm.make_perm(n);
    ni = n.a[0];
    nj = n.a[1];
    nh = n.a[2];
    f123.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f12.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f13.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f23.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f1.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f2.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f3.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    f0.resize(ni + 1, vector <vector <uint> > (nj + 1, vector <uint> (nh + 1, 0)));
    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        int l1, l2, l3, r1, r2, r3;
        cin >> l1 >> l2 >> l3 >> r1 >> r2 >> r3;
        Triple t = Triple(l1, l2, l3);
        t = perm.make_perm(t);
        l1 = t.a[0];
        l2 = t.a[1];
        l3 = t.a[2];
        t = Triple(r1, r2, r3);
        t = perm.make_perm(t);
        r1 = t.a[0];
        r2 = t.a[1];
        r3 = t.a[2];
        uint x;
        if (c == 'a') {
            cin >> x;
            update(l1, l2, l3, r1, r2, r3, x);
        } else {
            cout << query(l1, l2, l3, r1, r2, r3) << endl;
        }
    }
    return 0;
}
