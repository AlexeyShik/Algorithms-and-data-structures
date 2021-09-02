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
const ll mod = 10000;
const ll inf = 1e17;

constexpr int ALPHABET_SIZE = 'z' - 'a' + 1;
const int MAX_SIZE = 101;
map<char, int> char_to_id;

struct Node {
    int next[ALPHABET_SIZE]{};
    bool term{};
    int link{};
};

const string alph = "abcdefghijklmnopqrstuvwxyz";
Node nodes[MAX_SIZE];
int sz = 1;

void add_string(string &s) {
    int id = 0;
    for (char c : s) {
        int &next_id = nodes[id].next[char_to_id[c]];
        if (next_id == 0) {
            next_id = sz;
            nodes[sz++] = Node();
        }
        id = next_id;
    }
    nodes[id].term = true;
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
        for (char c : alph) {
            int id = char_to_id[c];
            if (node.next[id] != 0) {
                nodes[node.next[id]].link = (v == 0 ? 0 : link_node.next[id]);
                q.push(node.next[id]);
            } else {
                node.next[id] = link_node.next[id];
            }
        }
    }
}

ll add(ll a, ll b) {
    return (a + b) % mod;
}

ll sub(ll a, ll b) {
    return (a - b + mod) % mod;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll binpw(ll a, ll b) {
    if (b == 0) {
        return 1;
    }
    ll g = binpw(a, b / 2);
    return mul((b % 2 == 1 ? a : 1), mul(g, g));
}

vector<vector<ll>> mul(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    vector<vector<ll>> c(a.size(), vector<ll>(b[0].size()));
    for (int i = 0; i < (int) a.size(); ++i) {
        for (int j = 0; j < (int) b[0].size(); ++j) {
            for (int k = 0; k < (int) b.size(); ++k) {
                c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
            }
        }
    }
    return c;
}

vector<vector<ll>> binpw(vector<vector<ll>> &a, ll n) {
    if (n == 1) {
        return a;
    }
    auto b = binpw(a, n / 2);
    b = mul(b, b);
    if (n % 2 == 1) {
        b = mul(b, a);
    }
    return b;
}

int main() {
    fastio;
    int m, p;
    cin >> p;
    vector<string> bad;
    for (int i = 0; i < (int) alph.size(); ++i) {
        char_to_id[alph[i]] = i;
    }
    for (int i = 0; i < p; ++i) {
        string s;
        cin >> s;
        bad.push_back(s);
    }
    cin >> m;
    bool changes = true;
    while (changes) {
        changes = false;
        for (int i = 0; i < (int) bad.size(); ++i) {
            string s = bad[i];
            bool substr = false;
            for (int j = 0; j < (int) bad.size(); ++j) {
                if (i == j) {
                    continue;
                }
                string t = bad[j];
                for (int l = 0; l + t.size() <= s.size(); ++l) {
                    if (t == s.substr(l, t.size())) {
                        substr = true;
                        break;
                    }
                }
                if (substr) {
                    break;
                }
            }
            if (substr) {
                bad.erase(bad.begin() + i);
                changes = true;
                break;
            }
        }
    }
    for (string &s : bad) {
        add_string(s);
    }
    add_links();
    vector<vector<int>> nxt(sz, vector<int> (ALPHABET_SIZE, -1));
    for (int u = 0; u < sz; ++u) {
        Node &node = nodes[u];
        if (node.term) {
            continue;
        }
        for (char c : alph) {
            int id = char_to_id[c];
            int v = node.next[id];
            if (v != -1 && !nodes[v].term) {
                nxt[u][id] = v;
            }
        }
    }
    vector<vector<ll>> g(sz, vector<ll> (sz, 0));
    for (int u = 0; u < sz; ++u) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (nxt[u][i] != -1) {
                g[u][nxt[u][i]]++;
            }
        }
    }
    g = binpw(g, m);
    ll good = 0;
    for (int v = 0; v < sz; ++v) {
        if (!nodes[v].term) {
            good = add(good, g[0][v]);
        }
    }
    cout << sub(binpw(ALPHABET_SIZE, m), good);
    return 0;
}
