//
// Created by Alexey Shik on 23.04.2021.
//

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed)
#pragma GCC optimize("O3", "unroll-loops", "fast-math")

const int ALPHABET_SIZE = 27;
const int MAX_SIZE = (int) 2e5 + 10;

struct Node {
    int depth;
    int start;
    int par;
    int link;
    vector<int> next;

    inline Node(int depth, int start, int par) {
        this->depth = depth;
        this->start = start;
        this->par = par;
        link = -1;
        next = vector<int>(ALPHABET_SIZE);
        for (int &i : next) {
            i = -1;
        }
    }

    inline Node() : Node(-1, -1, -1) {}
};

int root = 0;
int sz = 1;
int s_sz = 0;
int id = 0;
int L, R;
string s;
vector<Node> nodes;

inline bool goDown(int R) {
    int currChar = s[R] - 'a' + 1;
    int par = nodes[id].par;
    if (nodes[id].depth != R - L) {
        int shift = R - L - nodes[par].depth;
        int edgeChar = s[nodes[id].start + shift] - 'a' + 1;
        if (edgeChar != currChar) {
            nodes[sz] = Node(R - L, nodes[id].start, par);
            nodes[par].next[s[nodes[id].start] - 'a' + 1] = sz;
            nodes[id].par = sz;
            nodes[id].start += shift;
            nodes[sz].next[edgeChar] = id;
            id = sz++;
        }
    }
    if (nodes[id].depth == R - L) {
        if (nodes[id].next[currChar] == -1) {
            nodes[sz] = Node((int) s.size(), R, id);
            nodes[id].next[currChar] = sz;
            id = sz++;
            return true;
        } else {
            id = nodes[id].next[currChar];
        }
    }
    return false;
}

void build() {
    s.resize(MAX_SIZE);
    nodes = vector<Node>(MAX_SIZE);
    L = 0;
    R = 0;
    nodes[root] = nodes[id] = Node(0, -1, -1);
    nodes[root].link = root;
    Node *nolink = nullptr;
    char x;
    while (cin >> x) {
        string t;
        cin >> t;
        for (char &c : t) {
            if (c < 'a') {
                c = (char) (c - 'A');
                c = (char) (c + 'a');
            }
        }
        if (x == '?') {
            int pos = 0;
            bool ok = true;
            int i = 0;
            while (i < (int) t.size() && ok) {
                pos = nodes[pos].next[t[i] - 'a' + 1];
                if (pos == -1) {
                    ok = false;
                    break;
                }
                int start = nodes[pos].start;
                int pard = nodes[nodes[pos].par].depth;
                int diff = nodes[pos].depth - pard;
                for (int j = start; j - start < min(diff, (int) t.size() - i); ++j) {
                    ok &= s[j] == t[i + j - start];
                }
                i += diff;
            }
            cout << (ok ? "YES" : "NO") << "\n";
        } else {
            for (int i = R; i - R < (int) t.size(); ++i) {
                s[i] = t[i - R];
            }
            s_sz += (int) t.size();
            while (R < s_sz) {
                while (L <= R) {
                    bool created = goDown(R);
                    if (nolink != nullptr) {
                        nolink->link = nodes[id].par;
                        nolink = nullptr;
                    }
                    if (!created) {
                        break;
                    }
                    id = nodes[id].par;
                    if (nodes[id].link == -1) {
                        nolink = &nodes[id];
                        id = nodes[id].par;
                    }
                    id = nodes[id].link;
                    L++;
                    while (nodes[id].depth < R - L) {
                        goDown(L + nodes[id].depth);
                    }
                }
                R++;
            }
        }
    }
}

int main() {
    fastio;
    build();
    return 0;
}