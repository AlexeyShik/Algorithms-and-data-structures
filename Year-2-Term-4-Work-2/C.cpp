//
// Created by Alexey Shik on 22.04.2021.
//

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

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

void build(string str) {
    nodes = vector<Node>(MAX_SIZE);
    s = std::move(str);
    L = 0;
    R = 0;
    nodes[root] = nodes[id] = Node(0, -1, -1);
    nodes[root].link = root;
    Node *nolink = nullptr;
    while (R < (int) s.size()) {
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

void print(int i) {
    for (int j : nodes[i].next) {
        if (j != -1) {
            cout << i + 1 << ' ' << j + 1 << ' ' << nodes[j].start + 1 << ' '
                 << min((int) s.size(), nodes[j].start + nodes[j].depth - nodes[i].depth) << endl;
            print(j);
        }
    }
}

void print() {
    cout << sz << ' ' << sz - 1 << endl;
    print(0);
}


int main() {
    string s;
    cin >> s;
    build(s);
    print();
    return 0;
}