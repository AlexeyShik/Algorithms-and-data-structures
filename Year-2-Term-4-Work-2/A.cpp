//
// Created by Alexey Shik on 18.04.2021.
//

#include <iostream>
#include <vector>

using namespace std;

constexpr int ALPHABET_SIZE = 'z' - 'a' + 1;
const int MAX_SIZE = 1e5;

int sz = 0;

struct node {
    vector<int> next = vector(ALPHABET_SIZE, -1);
};

node nodes[MAX_SIZE];

void add(string &&s) {
    int id = 0;
    for (char c : s) {
        int &next = nodes[id].next[c - 'a'];
        if (next == -1) {
            next = ++sz;
        }
        id = next;
    }
}

void print_order(int id) {
    for (char c = 'a'; c <= 'z'; ++c) {
        int &next = nodes[id].next[c - 'a'];
        if (next != -1) {
            cout << id + 1 << ' ' << next + 1 << ' ' << c << endl;
            print_order(next);
        }
    }
}

int main() {
    string s;
    cin >> s;
    for (int i = 0; i < (int) s.size(); ++i) {
        add(s.substr(i));
    }
    cout << sz + 1 << ' ' << sz << endl;
    print_order(0);
    return 0;
}