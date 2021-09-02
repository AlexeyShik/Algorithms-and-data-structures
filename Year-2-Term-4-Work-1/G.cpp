#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), \
cout.tie(0), cout.precision(20), cout.setf(ios::fixed)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll inf = 1e17;

constexpr int ALPHABET_SIZE = 'z' - 'a' + 1;
const int MAX_SIZE = 1e6 + 5;

struct Node {
    int next[ALPHABET_SIZE]{};
    vector<int> term{};
    int uplink{};
    int link{};
    bool used{};
};

Node nodes[MAX_SIZE];
int sz = 0;

void add_string(string &s, int i) {
    int id = 0;
    for (char c : s) {
        int &next_id = nodes[id].next[c - 'a'];
        if (next_id == 0) {
            next_id = ++sz;
            nodes[sz] = Node();
        }
        id = next_id;
    }
    nodes[id].term.push_back(i + 1);
}

void add_links() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        Node &node = nodes[v];
        int u = node.link;
        Node &link_node = nodes[u];
        if (u == 0) {
            node.uplink = 0;
        } else {
            node.uplink = !link_node.term.empty() ? u : link_node.uplink;
        }
        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            if (node.next[c] != 0) {
                nodes[node.next[c]].link = (v == 0 ? 0 : link_node.next[c]);
                q.push(node.next[c]);
            } else {
                node.next[c] = link_node.next[c];
            }
        }
    }
}

void get_ans(string &t, vector<bool> &ans) {
    int id = 0;
    t += "$";
    for (char c : t) {
        Node &node = nodes[id];
        int &next_id = node.next[c - 'a'];
        if (!node.used) {
            for (int x : node.term) {
                ans[x - 1] = true;
            }
            node.used = true;
            while (id != 0 && nodes[id].uplink != 0 && !nodes[nodes[id].uplink].used) {
                id = nodes[id].uplink;
                for (int x : nodes[id].term) {
                    ans[x - 1] = true;
                }
                nodes[id].used = true;
            }
        }
        id = next_id;
    }
}

int main() {
    fastio;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add_string(s, i);
    }
    add_links();
    string t;
    cin >> t;
    vector<bool> ans(n, false);
    get_ans(t, ans);
    for (bool x : ans) {
        cout << (x ? "YES" : "NO") << endl;
    }
    return 0;
}
