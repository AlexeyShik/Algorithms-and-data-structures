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

Node *insert(Node *root, Node *v) {
	if (!root)
		return v;
	v->par = root;
	if (root->key < v->key)
		root->right = insert(root->right, v);
	else
		root->left = insert(root->left, v);
	return root;
}

bool exists(Node *root, ll x) {
	if (!root)
		return false;
	if (root->key == x)
		return true;
	if (root->key < x)
		return exists(root->right, x);
	return exists(root->left, x);
}

Node *find(Node *root, ll x) {
	if (!root || root->key == x)
		return root;
	if (root->key < x)
		return find(root->right, x);
	return find(root->left, x);
}

ll find_min(Node *root) {
	if (!(root->left))
		return root->key;
	return find_min(root->left);
}

ll find_right_par(Node *root) {
	if (root->par == nullptr)
		return -1e9 - 7;
	if (root == root->par->left)
		return root->par->key;
	return find_right_par(root->par);
}

ll next(Node *root) {
	if (root->right != nullptr)
		return find_min(root->right);
	return find_right_par(root);
}

ll find_max(Node *root) {
	if (!(root->right))
		return root->key;
	return find_max(root->right);
}

ll find_left_par(Node *root) {
	if (root->par == nullptr)
		return 1e9 + 7;
	if (root == root->par->right)
		return root->par->key;
	return find_left_par(root->par);
}

ll prev(Node *root) {
	if (root->left != nullptr)
		return find_max(root->left);
	return find_left_par(root);
}

Node *erase(Node *root, ll x) {
	if (!root)
		return nullptr;
	if (root->key > x) {
		root->left = erase(root->left, x);
	}
	if (root->key < x) {
		root->right = erase(root->right, x);
	}
	if (root->key == x) {
		if (root->left != nullptr && root->right != nullptr) {
			root->key = find_min(root->right);
			root->right = erase(root->right, root->key);
		} else if (root->left != nullptr) {
			root->left->par = root->par;
			root = root->left;
		} else if (root->right != nullptr) {
			root->right->par = root->par;
			root = root->right;
		} else {
			root = nullptr;
		}
	}
	return root;
}

int main() {
    fastio;
    string s;
    Node *root = nullptr;
    ll maximal = -1e9 - 7, minimal = 1e9 + 7;
    while (cin >> s) {
    	ll x;
    	cin >> x;
    	if (s == "insert" && !exists(root, x)) {
    		root = insert(root, new Node(x));
    		if (root->par == nullptr)
    			root->par = root;
		} else if (s == "exists") {
			cout << (exists(root, x) ? "true" : "false") << endl;
		} else if (s == "next") {
			if (x >= maximal) {
				cout << "none" << endl;
			} else {
				if (!exists(root, x)) {
					root = insert(root, new Node(x));
					cout << next(find(root, x)) << endl;
					root = erase(root, x);
				} else {
					cout << next(find(root, x)) << endl;
				}
			}
		} else if (s == "delete") {
			if (exists(root, x))
				root = erase(root, x);
		} else if (s == "prev") {
			if (x <= minimal) {
				cout << "none" << endl;
			} else {
				if (!exists(root, x)) {
					root = insert(root, new Node(x));
					cout << prev(find(root, x)) << endl;
					root = erase(root, x);
				} else {
					cout << prev(find(root, x)) << endl;
				}
			}
		}
		if (root != nullptr) {
			maximal = find_max(root);
			minimal = find_min(root);
		} else {
			maximal = -1e9 - 7;
			minimal = 1e9 + 7;
		}
    }
    return 0;
}
