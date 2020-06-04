#include<iostream>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
int n, m, q;

struct rectangle {
    ll l, r, u, d;
    rectangle() = default;
    rectangle(ll l, ll r, ll u, ll d) : l(l), r(r), u(u), d(d) {}

    ll getArea() {
        return ((r - l) * (u - d)) % mod;
    }
};

rectangle intersection(rectangle const& A, rectangle const& B) {
    if (A.l > B.r || B.l > A.r || A.d > B.u || B.d > A.u) {
        return rectangle();
    }
    return rectangle(max(A.l, B.l), min(A.r, B.r), min(A.u, B.u), max(A.d, B.d));
}

istream& operator>> (istream& in, rectangle &r) {
    in >> r.l >> r.d >> r.r >> r.u;
    if (r.l > r.r) {
        swap(r.l, r.r);
    }
    if (r.d > r.u) {
        swap(r.d, r.u);
    }
    return in;
}

int log[128];
rectangle s[128][128][8][8];

void init() {
    log[0] = -1;
    for (int i = 1; i <= max(n, m); ++i) {
        log[i] = log[i / 2] + 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> s[i][j][0][0];
        }
    }

    for (int l = 1; l < 8; ++l) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j + (1 << l) <= m; ++j) {
                s[i][j][0][l] = intersection(s[i][j][0][l - 1],
                                             s[i][j + (1 << (l - 1))][0][l - 1]);
            }
        }
    }

    for (int k = 1; k < 8; ++k) {
        for (int i = 0; i + (1 << k) <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                s[i][j][k][0] = intersection(s[i][j][k - 1][0],
                                             s[i + (1 << (k - 1))][j][k - 1][0]);
            }
        }
    }

    for (int k = 1; k < 8; ++k) {
        for (int l = 1; l < 8; ++l) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                for (int j = 0; j + (1 << l) <= m; ++j) {
                    s[i][j][k][l] = intersection(
                            intersection(s[i][j][k - 1][l - 1],
                                    s[i + (1 << (k - 1))][j][k - 1][l - 1]),
                            intersection(s[i][j + (1 << (l - 1))][k - 1][l - 1],
                                    s[i + (1 << (k - 1))][j + (1 << (l - 1))][k - 1][l - 1]));
                }
            }
        }
    }
}

ll query(int li, int lj, int ri, int rj) {
    if (li > ri) {
        swap(li, ri);
    }
    if (lj > rj) {
        swap(lj, rj);
    }
    ++ri;
    ++rj;
    int logi = log[ri - li];
    int logj = log[rj - lj];
    return intersection(
            intersection(s[li][lj][logi][logj],
                    s[ri - (1 << logi)][lj][logi][logj]),
            intersection(s[li][rj - (1 << logj)][logi][logj],
                    s[ri - (1 << logi)][rj - (1 << logj)][logi][logj])).getArea();
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    init();
    ll a, b, v1, v2, v3, v4, ans = 0;
    cin >> q >> a >> b >> v4;
    while (q--) {
        v1 = (a * v4 + b) % mod;
        v2 = (a * v1 + b) % mod;
        v3 = (a * v2 + b) % mod;
        v4 = (a * v3 + b) % mod;
        ans += query(int(v1 % n), int(v2 % m), int(v3 % n), int(v4 % m));
        ans %= mod;
    }
    cout << ans;
    return 0;
}
