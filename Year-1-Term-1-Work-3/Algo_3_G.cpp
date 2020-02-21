#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;
typedef long long ll;
const ll inf = 1e15 + 7;
const int maxn = 6e5 + 5;
int sz = 0;
vector <ll> heap;
vector <int> index, indexof;

void makeSwap(int i, int j) {
	swap(heap[i], heap[j]);
    swap(index[indexof[i]], index[indexof[j]]);
    swap(indexof[i], indexof[j]);
}

void siftUp(int id) {
    if (id == 0)
        return;
    if (heap[id] > heap[(id - 1) / 2]) {
        makeSwap(id, (id - 1) / 2);
        siftUp((id - 1) / 2);
    }
}

void siftDown(int id) {
    if (heap[2 * id + 1] > heap[2 * id + 2] && heap[id] < heap[2 * id + 1]) {
        makeSwap(id, 2 * id + 1);
        siftDown(2 * id + 1);
    } else if (heap[id] < heap[2 * id + 2]) {
        makeSwap(id, 2 * id + 2);
        siftDown(2 * id + 2);
    }
}

ll extractMax() {
    ll ans = heap[0];
	--sz;
    heap[0] = heap[sz];
    int i = indexof[0];
    swap(index[i], index[indexof[sz]]);
    swap(indexof[0], indexof[sz]);
    indexof[sz] = -1;
    heap[sz] = -inf;
    siftDown(0);
    return ans;
}

void push(ll x, int y) {
    heap[sz] = x;
    index[y] = sz;
    indexof[sz] = y;
    siftUp(sz);
    ++sz;
}

void decreaseKey(int ind, ll d) {
    heap[index[ind]] = min(heap[index[ind]], d);
    siftUp(index[ind]);
}

void increaseKey(int ind, ll d) {
	heap[index[ind]] = max(heap[index[ind]], d);
	siftUp(index[ind]);
}

ll getKey(int ind) {
	return heap[index[ind]];
}

ll getMax() {
	return heap[0];
}

void erase(int ind) {
	increaseKey(ind, inf);
	extractMax();
}


int main() {
    heap.resize(maxn, -inf);
    index.resize(maxn, 0);
    indexof.resize(maxn, 0);
    int n, m;
    cin >> n >> m;
    vector <vector <pii> > lb(n), rb(n);
    vector <ll> ans(n, -inf);
    for (int i = 0; i < m; ++i) {
    	int l, r;
		ll t;
    	cin >> l >> r >> t;
    	l--, r--;
    	lb[l].push_back({t, i});
    	rb[r].push_back({t, i});
	}
	for (int i = 0; i < n; ++i) {
		for (auto pp : lb[i]) {
			push(pp.first, pp.second);
		}
		ans[i] = getMax();
		for (auto pp : rb[i])
			erase(pp.second);
	}
	for (int i = n - 2; i >= 0; --i)
		if (ans[i] == -inf)
			ans[i] = ans[i + 1];
	for (int i = 1; i < n; ++i)
		if (ans[i] == -inf)
			ans[i] = ans[i - 1];
	for (auto x : ans)
		cout << x << ' ';
    return 0;
}
