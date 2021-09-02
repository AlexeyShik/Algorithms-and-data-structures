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
    set<int> term{};
    int link{};
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
    nodes[id].term.insert(i);
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
        for (int x : link_node.term) {
            node.term.insert(x);
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

vector<int> get(string &t) {
    int id = 0;
    vector<int> ans;
    for (char c : t) {
        int &next_id = nodes[id].next[c - 'a'];
        ans.insert(ans.end(), nodes[next_id].term.begin(), nodes[next_id].term.end());
        id = next_id;
    }
    return ans;
}

int main() {
    string t;
    cin >> t;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add_string(s, i);
    }
    add_links();
    vector<bool> ans(n, false);
    for (int i : get(t)) {
        ans[i] = true;
    }
    for (bool x : ans) {
        cout << (x ? "Yes" : "No") << endl;
    }
    return 0;
}
