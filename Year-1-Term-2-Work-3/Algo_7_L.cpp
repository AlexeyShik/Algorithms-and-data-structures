#include <iostream>
#include <vector>
#include <algorithm>
#pragma GCC optimize("O3")

using namespace std;

typedef unsigned int uint;
const int maxn = (1 << 17);

vector <vector <uint> > tree;
vector <uint> val;

void pull(int id) {
    tree[id].resize(tree[2 * id + 1].size() + tree[2 * id + 2].size());
    merge(tree[2 * id + 1].begin(), tree[2 * id + 1].end(),
            tree[2 * id + 2].begin(), tree[2 * id + 2].end(), tree[id].begin());
}

void build(int id, int l, int r) {
    if (l == r - 1) {
        tree[id] = {val[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * id + 1, l, m);
    build(2 * id + 2, m, r);
    pull(id);
}

uint query(int id, int l, int r, int ql, int qr, uint x, uint y) {
    if (qr <= l || ql >= r) {
        return 0;
    }
    if (ql <= l && qr >= r) {
        return upper_bound(tree[id].begin(), tree[id].end(), y)
        - lower_bound(tree[id].begin(), tree[id].end(), x);
    }
    int m = (l + r) / 2;
    return query(2 * id + 1, l, m, ql, qr, x, y) + query(2 * id + 2, m, r, ql, qr, x, y);
}

uint a, b;
uint cur = 0;

uint nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}
uint nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    val.resize(maxn);
    tree.resize(2 * maxn);
    int q;
    cin >> q >> a >> b;
    for (int i = 0; i < maxn; ++i) {
        val[i] = nextRand24();
    }
    build(0, 0, maxn);
    uint ans = 0;
    while (q--) {
        int l = nextRand17(), r = nextRand17();
        if (l > r) {
            swap(l, r);
        }
        int x = nextRand24(), y = nextRand24();
        if (x > y) {
            swap(x, y);
        }
        uint c = query(0, 0, maxn, l, r + 1, x, y);
        b += c;
        ans += c;
    }
    cout << ans;
    return 0;
}
