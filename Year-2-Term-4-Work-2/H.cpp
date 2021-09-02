//
// Created by Alexey Shik on 22.04.2021.
//

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

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

    Node(int depth, int start, int par) {
        this->depth = depth;
        this->start = start;
        this->par = par;
        link = -1;
        next = vector<int>(ALPHABET_SIZE);
        for (int &i : next) {
            i = -1;
        }
    }

    Node() : Node(-1, -1, -1) {}
};

int root = 0;
int sz = 1;
int id = 0;
int L, R;
ll words = 0;
string s;
vector<Node> nodes;

bool goDown(int R) {
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

void build(int n) {
    s.resize(n);
    nodes = vector<Node>(MAX_SIZE);
    L = 0;
    R = 0;
    nodes[root] = nodes[id] = Node(0, -1, -1);
    nodes[root].link = root;
    Node *nolink = nullptr;
    while (R < n) {
        char x;
        cin >> x;
        if (x == '?') {
            if (R == 0) {
                s[R] = 'a';
            } else {
                for (char c = 'a'; c <= 'z'; ++c) {
                    int par = nodes[id].par;
                    int depth = 0;
                    if (par != -1) {
                        depth = nodes[par].depth;
                    }
                    if ((R - L == nodes[id].depth && nodes[id].next[c - 'a' + 1] != -1)
                        || (R - L != nodes[id].depth && s[nodes[id].start + R - L - depth] == c)) {
                        s[R] = c;
                        break;
                    }
                }
            }
            cout << s[R] << ' ';
        } else {
            s[R] = x;
        }
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
        words += L;
        if (x == '?') {
            cout << words << "\n";
        }
        R++;
    }
}

int main() {
    fastio;
    int n;
    cin >> n;
    build(n);
    return 0;
}