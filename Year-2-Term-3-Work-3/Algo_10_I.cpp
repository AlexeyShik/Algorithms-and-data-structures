#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

vector<pair<int, char>> path;
unordered_map<string, vector<pair<int, char>>> g;
unordered_map<string, int> first;
vector<bool> used;
int m = 0;

void gen(string &s, int d, int k) {
    if ((int) s.size() == k) {
        g[s.substr(0, s.size() - 1)].push_back({m++, s[s.size() - 1]});
        return;
    }
    for (int i = 0; i < d; ++i) {
        char c = (char) ('0' + i);
        s += c;
        gen(s, d, k);
        s.pop_back();
    }
}

int main() {
    fastio;
    int d, k;
    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; ++i) {
            char c = (char) ('0' + i);
            cout << c;
        }
        return 0;
    }
    string to_gen;
    gen(to_gen, d, k);
    used.resize(m, false);
    string start;
    for (int i = 0; i < k - 1; ++i) {
        start += "0";
    }
    stack<string> st;
    stack<pair<int, char>> st_pa;
    st.push(start);
    while (!st.empty()) {
        string u = st.top();
        if (first[u] == (int) g[u].size()) {
            if (!st_pa.empty()) {
                path.push_back(st_pa.top());
                st_pa.pop();
            }
            st.pop();
        }
        while (first[u] != (int) g[u].size()) {
            if (used[g[u][first[u]].first]) {
                ++first[u];
                continue;
            }
            auto e = g[u][first[u]++];
            used[e.first] = true;
            st.push(move(u.substr(1, u.size()) + e.second));
            st_pa.push({e.first, e.second});
            break;
        }
    }
    reverse(path.begin(), path.end());
    cout << start;
    for (auto &pp : path) {
        cout << pp.second;
    }
    return 0;
}
