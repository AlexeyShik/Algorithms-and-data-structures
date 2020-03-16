#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

// old code

using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e18;

struct node {
    ll x, y, sz, sum;
    node *left, *right;
    node(ll val){
        x = val;
        sz = 1;
        sum = x;
        y = (rand() << 15) | rand();
        left = right = nullptr;
    }
};

ll sz(node * root) {
	if (!root)
		return 0;
	return root->sz;
}

ll sum(node * root) {
	if (!root)
		return 0;
	return root->sum;
}

void update(node * root) {
	if (!root)
		return;
	root->sz = sz(root->left) + 1 + sz(root->right);
	root->sum = sum(root->left) + root->x + sum(root->right);
}

void print(node * root) {
	if (!root)
		return;
	print(root->left);
	cout << "!!!   " << root->x << " " << root->y << endl;
	print(root->right);
}

pair <node *, node *> split(node * root, ll val) {
    if (!root)
        return {nullptr, nullptr};
    if (root->x < val) {
        pair <node *, node *> res = split(root->right, val);
        root->right = res.first;
        update(root);
        return{root, res.second};
    } else {
        pair <node *, node *> res = split(root->left, val);
        root->left = res.second;
        update(root);
        return {res.first, root};
    }
}

node * merge(node * root1, node * root2) {
    if (!root1) {
        return root2;
	}
	if (!root2) {
        return root1;
    }
    if (root1->y < root2->y) {
        root1->right = merge(root1->right, root2);
        update(root1);
        return root1;
    } else {
        root2->left = merge(root1, root2->left);
        update(root2);
        return root2;
    }
}

bool find(node * root, ll val) {
	if (!root)
		return false;
	if (root->x == val)
		return true;
	if (val < root->x)
		return find(root->left, val);
	else
		return find(root->right, val);
}

node * insert(node * root, node * v) {
    if (!root)
    	return v;
    if (!v)
    	return root;
    if (v->y < root->y) {
    	auto p = split(root, v->x);
    	v->left = p.first;
    	v->right = p.second;
    	update(v);
    	return v;
	}
	if (v->x < root->x)
		root->left = insert(root->left, v);
	else
		root->right = insert(root->right, v);
	update(root);
	return root;
}

node * erase(node * root, ll val) {
	if (!root)
		return nullptr;
	if (root->x == val)
		return merge(root->left, root->right);
	if (val < root->x)
		root->left = erase(root->left, val);
	else
		root->right = erase(root->right, val);
	update(root);
	return root;
}

ll sumq(node * root, ll l, ll r) {
	if (!root)
		return 0;
	auto p1 = split(root, r + 1);
	auto p2 = split(p1.first, l);
	ll ans = sum(p2.second);
	root = merge(merge(p2.first, p2.second), p1.second);
	return ans;
}

int main() {
	node *root = nullptr;
	int n;
	cin >> n;
	ll add = 0;
	for (int i = 0; i < n; ++i) {
		char c;
		cin >> c;
		if (c == '+') {
			ll x;
			cin >> x;
			if (!find(root, (x + add) % mod))
				root = insert(root, new node((x + add) % mod));
			add = 0;
		} else {
			int l, r;
			cin >> l >> r;
			add = sumq(root, l, r);
			cout << add << endl;
		}
	}
	return 0;
}
