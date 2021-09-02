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
const int MAX_SIZE = 2e6 + 5;

struct Node {
    int next[ALPHABET_SIZE]{};
    bool term{};
    int uplink{};
    int link{};
    bool used{};
    int count{};
};

Node nodes[MAX_SIZE];
int sz = 0;

int add_string(string &s) {
    int id = 0;
    for (char c : s) {
        int &next_id = nodes[id].next[c - 'a'];
        if (next_id == 0) {
            next_id = ++sz;
            nodes[sz] = Node();
        }
        id = next_id;
    }
    nodes[id].term = true;
    return id;
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
        node.uplink = node.term ? v : link_node.uplink;
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

void update(string &s) {
    int id = 0;
    vector<int> used_nodes;
    for (char c : s) {
        id = nodes[id].next[c - 'a'];
        int term = nodes[id].uplink;
        while (!nodes[term].used) {
            ++nodes[term].count;
            nodes[term].used = true;
            used_nodes.push_back(term);
            term = nodes[nodes[term].link].uplink;
        }
    }
    for (int i : used_nodes) {
        nodes[i].used = false;
    }
}

int main() {
    fastio;
    int n;
    cin >> n;
    vector<int> map_to_node(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        map_to_node[i] = add_string(s);
    }
    add_links();
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            string s;
            cin >> s;
            update(s);
        } else {
            int u;
            cin >> u;
            --u;
            cout << nodes[map_to_node[u]].count << endl;
        }
    }
    return 0;
}
