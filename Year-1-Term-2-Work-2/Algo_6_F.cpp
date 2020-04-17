#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int k;
    cin >> k;
    int d = (1 << (int)(log2(2 * k - 1)));
    for (int i = 0; i < k; ++i) {
        int n = d + i;
        string s;
        while (n > 0) {
            cout << (n % 2 ? "ZZ" : "Yy");
            n /= 2;
        }
        cout << endl;
    }
    return 0;
}
