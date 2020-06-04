#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
const ll inf = 1e18, maxn = 1e5 + 1;

vector <ll> pro(4 * maxn, 0), maxi(4 * maxn, 0), maxpos(4 * maxn, 0);

inline void pull(int id) {
    if (maxi[2 * id + 1] > maxi[2 * id + 2]) {
        maxi[id] = maxi[2 * id + 1];
        maxpos[id] = maxpos[2 * id + 1];
    } else {
        maxi[id] = maxi[2 * id + 2];
        maxpos[id] = maxpos[2 * id + 2];
    }
}

inline void relax(int id, int child) {
    pro[child] += pro[id];
}

inline void propogate(int id) {
    if (2 * id + 1 < 4 * maxn) {
        relax(id, 2 * id + 1);
    }
    if (2 * id + 2 < 4 * maxn) {
        relax(id, 2 * id + 2);
    }
    pro[id] = 0;
}

inline void push(int id) {
    maxi[id] += pro[id];
    propogate(id);
}

inline void build(int id, int l, int r) {
    if (l == r - 1) {
        maxi[id] = 0;
        maxpos[id] = l;
        return;
    }
    int m = (l + r) / 2;
    build(2 * id + 1, l, m);
    build(2 * id + 2, m, r);
    pull(id);
}

inline void update(int id, int l, int r, int ql, int qr, int d) {
    push(id);
    if (ql <= l && qr >= r) {
        pro[id] = d;
        push(id);
        return;
    }
    if (qr <= l || ql >= r)
        return;
    int m = (l + r) / 2;
    update(2 * id + 1, l, m, ql, qr, d);
    update(2 * id + 2, m, r, ql, qr, d);
    pull(id);
}

inline pair<int, int> query(int id) {
    push(id);
    return {maxi[id], maxpos[id]};
}

struct Event {
    int type = 0;
    int x = 0;
    int y1 = 0, y2 = 0;
    Event() = default;
    Event(int type, int x, int y1, int y2) : type(type), x(x), y1(y1), y2(y2) {}
};

bool cmp(const Event &a, const Event &b) {
    if (a.x < b.x) {
        return true;
    } else if (a.x > b.x) {
        return false;
    }
    return a.type <= b.type;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n = 50000;
    cin >> n;
    map <int, int> compress;
    map <int, int> ret_compress;
    set <int> ys;
    vector <vector <int> > tmp(n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        tmp[i].push_back(x1);
        tmp[i].push_back(y1);
        tmp[i].push_back(x2);
        tmp[i].push_back(y2);
        ys.insert(y1);
        ys.insert(y2);
    }
    for (int y : ys) {
        compress[y] = compress.size();
        ret_compress[compress.size() - 1] = y;
    }
    vector <Event> events(3 * n);
    for (int i = 0; i < n; ++i) {
        events[3 * i] = (Event(-1, tmp[i][0], compress[tmp[i][1]], compress[tmp[i][3]]));
        events[3 * i + 1] = (Event(0, tmp[i][2], compress[tmp[i][1]], compress[tmp[i][3]]));
        events[3 * i + 2] = (Event(1, tmp[i][2], compress[tmp[i][1]], compress[tmp[i][3]]));
    }
    stable_sort(events.begin(), events.end(), cmp);
    build(0, 0, maxn);
    int ans = 0;
    pair <int, int> pos = {0, 0};
    for (Event e : events) {
        if (e.type == 0) {
            auto curr = query(0);
            if (curr.first > ans) {
                ans = curr.first;
                pos = {e.x, ret_compress[curr.second]};
            }
        } else {
            update(0, 0, maxn, e.y1, e.y2 + 1, -e.type);
        }
    }
    cout << ans << endl << pos.first << ' ' << pos.second;
    return 0;
}
