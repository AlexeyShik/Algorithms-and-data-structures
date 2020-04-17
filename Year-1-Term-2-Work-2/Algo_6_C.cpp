#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("linkedmap.in", "r", stdin), freopen("linkedmap.out", "w", stdout)
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;
const int funcs = 1e5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

vector <int> simple = {1000003, 1000033, 1000037, 1000039,
                       1000081, 1000099, 1000117, 1000121, 1000133, 1000151};

struct hash_func {
    int a, b, p;
    hash_func(int a, int b, int p) {
        this->a = a;
        this->b = b;
        this->p = p;
    }
    int get_id(int x) {
        return (int)((1ll * a * x + b + mod) % p);
    }
};

vector <hash_func> h;

void fill() {
    for (int a = 1; a <= 100; ++a) {
        for (int b = 1; b <= 100; ++b) {
            for (int i = 0; i < 10; ++i) {
                h.emplace_back(a, b, simple[i]);
            }
        }
    }
}

struct string_hash {
    int h1, h2;
    string_hash(const string &s) {
        h1 = h2 = 0;
        for (char c : s) {
            h1 = (h1 * 41 + (int)c) % (int)(1e9 + 7);
            h2 = (h2 * 43 + (int)c) % (int)(1e9 + 9);
        }
    }
    bool operator ==(const string_hash &right) {
        return h1 == right.h1 && h2 == right.h2;
    }
};

struct ordered_node;

struct node {
    string val;
    node *next;
    ordered_node *to_ordered_node;
    node(const string &x) {
        val = x;
        next = nullptr;
        to_ordered_node = nullptr;
    }
};

struct ordered_node {
    node *to_node;
    ordered_node *prev;
    ordered_node *next;
};

struct hash_map {
    size_t m;
    int j;
    vector <list<node*>> nodes;
    ordered_node *last = nullptr;
    vector <list<string_hash> > hashx;
    vector <list<pair<string, string> > > str;
    hash_map(int m) {
        fill();
        this->m = m;
        j = rand() % funcs;
        hashx.resize(m);
        str.resize(m);
        nodes.resize(m);
    }
    bool exists(const string_hash &hx, const string &s) {
        int i = h[j].get_id(hx.h1) % m;
        auto p2 = str[i].begin();
        for (auto p1 = hashx[i].begin(); p1 != hashx[i].end(); ++p1, ++p2) {
            if (*p1 == hx && p2->second == s) {
                return true;
            }
        }
        return false;
    }
    void put(const string &x, const string &y) {
        auto hx = string_hash(x);
        if (exists(hx, y)) {
            return;
        }
        int i = h[j].get_id(hx.h1) % m;
        auto p2 = str[i].begin();
        for (auto p1 = hashx[i].begin(); p1 != hashx[i].end(); ++p1, ++p2) {
            if (*p1 == x) {
                (*p2).second = y;
                return;
            }
        }
        hashx[i].push_back(hx);
        str[i].push_back({x, y});
        auto *tmp = new node(x);
        auto *omp = new ordered_node();
        omp->to_node = tmp;
        tmp->to_ordered_node = omp;
        omp->next = nullptr;
        omp->prev = last;
        if (last != nullptr) {
            last->next = omp;
        }
        last = omp;
        nodes[i].push_back(tmp);
    }
    string get(const string &x) {
        auto pp = string_hash(x);
        int i = h[j].get_id(pp.h1) % m;
        auto p2 = str[i].begin();
        for (auto p1 = hashx[i].begin(); p1 != hashx[i].end(); ++p1, ++p2) {
            if (*p1 == pp) {
               return p2->second;
            }
        }
        return "none";
    }
    void del_node(ordered_node *o) {
        if (o->prev) {
            o->prev->next = o->next;
        }
        if (o->next) {
            o->next->prev = o->prev;
        } else {
            last = o->prev;
        }
    }
    void erase(const string &x) {
        auto hx = string_hash(x);
        int i = h[j].get_id(hx.h1) % m;
        auto p2 = str[i].begin();
        auto p3 = nodes[i].begin();
        for (auto p1 = hashx[i].begin(); p1 != hashx[i].end(); ++p1, ++p2, ++p3) {
            if (*p1 == hx) {
                hashx[i].erase(p1);
                str[i].erase(p2);
                del_node((*p3)->to_ordered_node);
                free((*p3)->to_ordered_node);
                nodes[i].erase(p3);
                return;
            }
        }
    }
    string next(const string &x) {
        auto hx = string_hash(x);
        int i = h[j].get_id(hx.h1) % m;
        auto p3 = nodes[i].begin();
        for (auto p1 = hashx[i].begin(); p1 != hashx[i].end(); ++p1, ++p3) {
            if (*p1 == hx) {
                auto o = (*p3)->to_ordered_node;
                if (o->next) {
                    return o->next->to_node->val;
                } else {
                    return "none";
                }
            }
        }
        return "none";
    }
    string prev(const string &x) {
        auto hx = string_hash(x);
        int i = h[j].get_id(hx.h1) % m;
        auto p3 = nodes[i].begin();
        for (auto p1 = hashx[i].begin(); p1 != hashx[i].end(); ++p1, ++p3) {
            if (*p1 == hx) {
                auto o = (*p3)->to_ordered_node;
                if (o->prev) {
                    return o->prev->to_node->val;
                } else {
                    return "none";
                }
            }
        }
        return "none";
    }
};

int main() {
    fastio;
    fileio;
    srand(time(nullptr));
    fill();
    hash_map hm(2e5);
    string s;
    while (cin >> s) {
        string x;
        cin >> x;
        if (s == "put") {
            string y;
            cin >> y;
            hm.put(x, y);
        } else if (s == "get") {
            cout << hm.get(x) << endl;
        } else if (s == "delete") {
            hm.erase(x);
        } else if (s == "next") {
            cout << hm.get(hm.next(x)) << endl;
        } else {
            cout << hm.get(hm.prev(x)) << endl;
        }
    }
    return 0;
}
