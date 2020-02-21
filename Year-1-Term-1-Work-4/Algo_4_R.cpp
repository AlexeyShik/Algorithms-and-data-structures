#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define pii pair<int, int>

using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 7;
const int maxn = 1001;

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    int n;
    cin >> n;
    if (n < 10) {
        cout << n;
        return 0;
    }
    vector <vector <bool> > used(maxn, vector <bool> (maxn));
    vector <vector <pii> > prev(maxn, vector <pii> (maxn));
    vector <vector <int> > dig(maxn, vector <int> (maxn));
    used[0][0] = true;
    prev[0][0] = {-1, -1};
    queue <pii> q;
    for (int i = 1; i < 10; ++i) {
        q.push({i, i});
        prev[i][i] = {-1, -1};
        dig[i][i] = i;
        used[i][i] = true;
    }
    pii last = {-1, -1};
    while (true) {
        pii cur = q.front();
        q.pop();
        if (cur == make_pair(n, 0)) {
            last = cur;
            break;
        }
        for (int i = 0; i < 10; ++i) {
            pii next = {cur.first + i, (cur.second * 10 + i) % n};
            if (next.first <= n && !used[next.first][next.second]) {
                used[next.first][next.second] = true;
                q.push(next);
                prev[next.first][next.second] = cur;
                dig[next.first][next.second] = i;
            }
        }
    }
    vector <int> ans;
    while (last != make_pair(-1, -1)) {
        ans.push_back(dig[last.first][last.second]);
        last = prev[last.first][last.second];
    }
    reverse(ans.begin(), ans.end());
    for (int x : ans)
        cout << x;
    return 0;
}

