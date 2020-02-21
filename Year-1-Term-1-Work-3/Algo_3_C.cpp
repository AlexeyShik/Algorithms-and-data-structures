#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9 + 7;
int sz = 0;
vector <int> heap, index, indexof;

void makeSwap(int i, int j) {
	swap(heap[i], heap[j]);
    swap(index[indexof[i]], index[indexof[j]]);
    swap(indexof[i], indexof[j]);
}

void siftUp(int id) {
    if (id == 0)
        return;
    if (heap[id] < heap[(id - 1) / 2]) {
        makeSwap(id, (id - 1) / 2);
        siftUp((id - 1) / 2);
    }
}

void siftDown(int id) {
    if (heap[2 * id + 1] < heap[2 * id + 2] && heap[id] > heap[2 * id + 1]) {
        makeSwap(id, 2 * id + 1);
        siftDown(2 * id + 1);
    } else if (heap[id] > heap[2 * id + 2]) {
        makeSwap(id, 2 * id + 2);
        siftDown(2 * id + 2);
    }
}

void extractMin() {
    int ans = heap[0];
    if (ans == inf) {
        cout << '*' << endl;
        return;
    }
	--sz;
    heap[0] = heap[sz];
    int i = indexof[0];
    swap(index[i], index[indexof[sz]]);
    swap(indexof[0], indexof[sz]);
    indexof[sz] = -1;
    heap[sz] = inf;
    siftDown(0);
    cout << ans << ' ' << i << endl;
}

void push(int x, int y) {
    heap[sz] = x;
    index[y] = sz;
    indexof[sz] = y;
    siftUp(sz);
    ++sz;
}

void decreaseKey(int ind, int d) {
    heap[index[ind]] = min(heap[index[ind]], d);
    siftUp(index[ind]);
}

int main() {
    heap.resize(1e6, inf);
    index.resize(1e6, -1);
    indexof.resize(1e6, -1);
    string s;
    int k = 1;
    while (cin >> s) {
        if (s == "push") {
            int x;
            cin >> x;
            push(x, k);
        } else if (s == "extract-min") {
            extractMin();
        } else if (s == "decrease-key") {
            int i, d;
            cin >> i >> d;
            if (indexof[index[i]] == -1)
                continue;
            decreaseKey(i, d);
        }
        ++k;
    }
    return 0;
}
