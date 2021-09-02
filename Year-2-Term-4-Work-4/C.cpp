#include <iostream>
#include <vector>
#include <cmath>

#define fastio ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;

typedef long long ll;

vector<bool> gen_primes(int n) {
    vector<bool> prime(n);
    for (int i = 2; i < n; ++i) {
        prime[i] = true;
    }
    for (ll i = 2; i * i <= n; ++i) {
        if (prime[(int) i]) {
            for (ll j = i * i; j < n; j += i) {
                prime[(int) j] = false;
            }
        }
    }
    return prime;
}

int calc_h(vector<bool> &primes, int x) {
    int h = 0;
    for (int i = 0; i < (int) primes.size(); ++i) {
        if (primes[i]) {
            h = h * x + i;
        }
    }
    return h;
}

int calc_h(vector<bool> &&primes, int x) {
    return calc_h(primes, x);
}

int main() {
    fastio;
    int n, x;
    cin >> n >> x;
    if (n < 10) {
        cout << calc_h(gen_primes(n + 1), x);
    } else {
        int sq = (int) sqrt(n) + 1;
        vector<bool> prime = gen_primes(sq);
        int h = calc_h(prime, x);
        vector<int> primes;
        for (int i = 2; i < sq; ++i) {
            if (prime[i]) {
                primes.push_back(i);
            }
        }
        for (int k = sq; k < n; k += sq) {
            prime.assign(sq, true);
            for (int p : primes) {
                int sqp = p * p;
                if (sqp > k + sq) {
                    break;
                }
                int beg;
                if (sqp < k) {
                    int rem = k % p;
                    beg = rem == 0 ? 0 : p - rem;
                } else {
                    beg = sqp - k;
                }
                for (int j = beg; j < sq; j += p) {
                    prime[j] = false;
                }
            }
            for (int i = 0; i < sq && i + k <= n; ++i) {
                if (prime[i]) {
                    h = h * x + (int) (i + k);
                }
            }
        }
        cout << h;
    }
    return 0;
}
