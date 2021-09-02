#include <iostream>
#include <vector>

#pragma GCC optimize("O3", "unroll-loops", "fast-math")
#define fastio ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;

typedef long long ll;
const int MAXN = 2e7 + 1;

vector<bool> gen_primes() {
    vector<bool> prime(MAXN);
    for (int i = 2; i < MAXN; ++i) {
        prime[i] = true;
    }
    for (ll i = 2; i * i <= MAXN; ++i) {
        if (prime[(int) i]) {
            for (ll j = i * i; j < MAXN; j += i) {
                prime[(int) j] = false;
            }
        }
    }
    return prime;
}

int main() {
    fastio;
    int n;
    cin >> n;
    vector<bool> prime = gen_primes();
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cout << (prime[x] ? "YES" : "NO") << endl;
    }
    return 0;
}
