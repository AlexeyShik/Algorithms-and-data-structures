#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
 
using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 7;
 
struct Node {
    ll key;
    Node *left, *right, *par;
    Node(ll key) {
        this->key = key;
        left = right = par = nullptr;
    }
};
 
Node *to_splay = nullptr;
Node *main_root = nullptr;
 
void rotate(Node *v) {
    if (!v)
        return;
    Node *p = v->par;
    if (!p || p == v)
        return;
    Node *g = p->par;
    p->par = v;
    if (p->left == v) {
        p->left = v->right;
        if (v->right != nullptr)
            v->right->par = p;
        v->right = p;
    } else {
        p->right = v->left;
        if (v->left != nullptr)
            v->left->par = p;
        v->left = p;
    }
    if (g != p && g != nullptr) {
        v->par = g;
        if (g->left == p) {
            g->left = v;
        } else {
            g->right = v;
        }
    } else {
        v->par = v;
    }
}
 
void zig_zig(Node *v) {
    rotate(v->par);
    rotate(v);
}
 
void zig_zag(Node *v) {
    rotate(v);
    rotate(v);
}
 
void splay(Node* &v) {
    if (!v)
        return;
    if (!(v->par)) {
        v->par = v;
        return;
    }
    while (v->par != v) {
        if (v->par->par != nullptr && v->par->par == v->par) {
            rotate(v);
        } else if (v->par->par != nullptr) {
            if ((v->par->par->left == v->par) ^ (v->par->left == v)) {
                zig_zag(v);
            } else {
                zig_zig(v);
            }
        }
    }
    v->par = v;
}
 
Node *sift_down(Node *root, ll x) {  //  don't splay
    if (!root)
        return nullptr;
    Node *tmp = root;
    while ((tmp->key < x && tmp->right != nullptr)
        || (tmp->key > x && tmp->left != nullptr)) {
        if (tmp->key < x) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }
    return tmp;
}
 
Node *insert(Node *root, Node *v) {
    if (!root)
        return v;
    Node *tmp = sift_down(root, v->key);
    v->par = tmp;
    if (tmp->key < v->key) {
        tmp->right = v;
    } else {
        tmp->left = v;
    }
    splay(v);
    return v;
}
 
bool exists(Node* &root, ll x) {
    if (!root)
        return false;
    if (root->key == x)
        return true;
    Node *tmp = sift_down(root, x);
    splay(tmp);
    root = tmp;
    return root->key == x;
}
 
Node *find(Node *root, ll x) {
    if (!root)
        return nullptr;
    if (root->key == x)
        return root;
    Node *tmp = sift_down(root, x);
    splay(tmp);
    root = tmp;
    return root;
}
 
Node *find_min(Node *root) {  //  don't splay
    if (!(root->left))
        return root;
    return find_min(root->left);
}
 
ll find_right_par(Node *root) {  //  don't splay
    if (root->par == nullptr)
        return -1e9 - 7;
    if (root == root->par->left)
        return root->par->key;
    return find_right_par(root->par);
}
 
ll next(Node *root) {
    if (root->right != nullptr) {
        Node *v = find_min(root->right);
        splay(v);
        main_root = v;
        return v->key;
    }
    ll ans = find_right_par(root);
    splay(root);
    main_root = root;
    return ans;
}
 
Node *find_max(Node* &root) {  //  don't splay
    if (!(root->right))
        return root;
    return find_max(root->right);
}
 
ll find_left_par(Node *root) {  //  don't splay
    if (root->par == nullptr)
        return 1e9 + 7;
    if (root == root->par->right)
        return root->par->key;
    return find_left_par(root->par);
}
 
ll prev(Node *root) {
    if (root->left != nullptr) {
        Node *v = find_max(root->left);
        splay(v);
        main_root = v;
        return v->key;
    }
    ll ans = find_left_par(root);
    splay(root);
    main_root = root;
    return ans;
}
 
Node *merge(Node *a, Node *b) {
    if (!a && !b)
        return nullptr;
    if (!a) {
        b->par = b;
        return b;
    }
    if (!b) {
        a->par = a;
        return a;
    }
    a->par = a;
    b->par = b;
    Node *v = find_max(a);
    splay(v);
    v->right = b;
    b->par = v;
    return v;
}
 
Node *erase(Node *root, ll x) {
    if (!root)
        return nullptr;
    Node *v = find(root, x);
    return merge(v->left, v->right);
}
 
int main() {
    fastio;
    string s;
    main_root = nullptr;
    ll maximal = -1e9 - 7, minimal = 1e9 + 7;
    while (cin >> s) {
        ll x;
        cin >> x;
        if (s == "insert" && !exists(main_root, x)) {
            main_root = insert(main_root, new Node(x));
        } else if (s == "exists") {
            cout << (exists(main_root, x) ? "true" : "false") << endl;
        } else if (s == "next") {
            if (x >= maximal) {
                cout << "none" << endl;
            } else {
                if (!exists(main_root, x)) {
                    main_root = insert(main_root, new Node(x));
                    cout << next(find(main_root, x)) << endl;
                    main_root = erase(main_root, x);
                } else {
                    cout << next(find(main_root, x)) << endl;
                }
            }
        } else if (s == "delete") {
            if (exists(main_root, x))
                main_root = erase(main_root, x);
        } else if (s == "prev") {
            if (x <= minimal) {
                cout << "none" << endl;
            } else {
                if (!exists(main_root, x)) {
                    main_root = insert(main_root, new Node(x));
                    cout << prev(find(main_root, x)) << endl;
                    main_root = erase(main_root, x);
                } else {
                    cout << prev(find(main_root, x)) << endl;
                }
            }
        }
        if (main_root != nullptr) {
            Node *v = find_max(main_root);
            maximal = v->key;
            splay(v);
            main_root = v;
            v = find_min(main_root);
            minimal = v->key;
            splay(v);
            main_root = v;
        } else {
            maximal = -1e9 - 7;
            minimal = 1e9 + 7;
        }
        if (main_root != nullptr)
            main_root->par = main_root;
    }
    return 0;
}
