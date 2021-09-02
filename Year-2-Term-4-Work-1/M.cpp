#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), \
cout.tie(0), cout.precision(20), cout.setf(ios::fixed)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll inf = 1e17;

#include <cstdint>
#include <stdexcept>
#include <climits>

#include <string>
#include <functional>

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

struct big_integer {
    ///  @variables
 private:
    std::vector<uint32_t> data;
    bool sign;

    ///  @consts and @typedefs
 private:
    static const uint64_t BASE = static_cast<uint64_t>(UINT32_MAX) + 1;
    using uint128_t = uint64_t;
    using func = std::function<uint32_t(uint32_t, uint32_t)>;

    ///  @methods
 public:
    big_integer();

    big_integer(const big_integer &other);

    big_integer(int a);

    explicit big_integer(uint32_t a);

    explicit big_integer(const std::string &str);

    ~big_integer();

    big_integer &operator=(const big_integer &other);

    big_integer &operator+=(const big_integer &rhs);

    big_integer &operator-=(const big_integer &rhs);

    big_integer &operator*=(const big_integer &rhs);

    big_integer &operator/=(const big_integer &rhs);

    big_integer &operator%=(const big_integer &rhs);

    big_integer &operator&=(const big_integer &rhs);

    big_integer &operator|=(const big_integer &rhs);

    big_integer &operator^=(const big_integer &rhs);

    big_integer &operator<<=(int rhs);

    big_integer &operator>>=(int rhs);

    big_integer operator+() const;

    big_integer operator-() const;

    big_integer operator~() const;

    big_integer &operator++();

    big_integer operator++(int);

    big_integer &operator--();

    big_integer operator--(int);

    friend bool operator==(const big_integer &a, const big_integer &b);

    friend bool operator!=(const big_integer &a, const big_integer &b);

    friend bool operator<(const big_integer &a, const big_integer &b);

    friend bool operator>(const big_integer &a, const big_integer &b);

    friend bool operator<=(const big_integer &a, const big_integer &b);

    friend bool operator>=(const big_integer &a, const big_integer &b);

    friend std::string to_string(const big_integer &a);

 private:
    size_t size() const;

    uint32_t &operator[](size_t i);

    const uint32_t &operator[](size_t i) const;

    uint32_t get_kth(size_t k) const;

    void fill_back(size_t n, uint32_t value);  //  дописывает value в конец числа n раз

    static uint32_t low32_bits(uint64_t a);
    static uint32_t high32_bits(uint64_t a);

    static size_t bit_count(uint32_t a);

    uint32_t count() const;  //  количество единичных бит числа

    uint32_t clear_log2() const;  // логарифм от степени двойки

    static std::pair<big_integer, uint32_t> short_div(const big_integer &a, uint32_t b);
    //  {целая часть, остаток}

    uint32_t trial(uint64_t k, uint64_t m, const big_integer &d) const;

    bool smaller(const big_integer &dq, uint64_t k, uint64_t m) const;

    void difference(const big_integer &dq, uint64_t k, uint64_t m);

    void to_additional_code(size_t n_digits);

    big_integer &bitwise_operation(const big_integer &rhs, const func &f);

    void shrink_to_fit();
};

big_integer operator+(big_integer a, const big_integer &b);

big_integer operator-(big_integer a, const big_integer &b);

big_integer operator*(big_integer a, const big_integer &b);

big_integer operator/(big_integer a, const big_integer &b);

big_integer operator%(big_integer a, const big_integer &b);

big_integer operator&(big_integer a, const big_integer &b);

big_integer operator|(big_integer a, const big_integer &b);

big_integer operator^(big_integer a, const big_integer &b);

big_integer operator<<(big_integer a, int b);

big_integer operator>>(big_integer a, int b);

bool operator==(const big_integer &a, const big_integer &b);

bool operator!=(const big_integer &a, const big_integer &b);

bool operator<(const big_integer &a, const big_integer &b);

bool operator>(const big_integer &a, const big_integer &b);

bool operator<=(const big_integer &a, const big_integer &b);

bool operator>=(const big_integer &a, const big_integer &b);

std::string to_string(const big_integer &a);

std::ostream &operator<<(std::ostream &s, const big_integer &a);

#endif  //  BIG_INTEGER_H

big_integer::big_integer() : data(1), sign(false) {}

big_integer::big_integer(const big_integer &other) = default;

big_integer::big_integer(const int a) : data(1), sign(a < 0) {
    data[0] = (a == INT_MIN ? static_cast<uint32_t>(INT_MAX) + 1 : abs(a));
}

big_integer::big_integer(const uint32_t a) : data(1, a), sign(false) {}

big_integer::big_integer(const std::string &str) : big_integer() {
    if (str.empty()) {
        throw std::runtime_error("Expected: integer, found: empty string");
    }
    big_integer base = 1;
    for (ptrdiff_t i = str.size() - 1; i >= 0 && str[i] != '-'; --i) {
        if (!isdigit(str[i])) {
            throw std::runtime_error("Expected: digit, found: " + std::string(1, str[i]));
        }
        *this += base * static_cast<uint32_t>(str[i] - '0');
        base *= 10;
    }
    sign = (str[0] == '-');
    shrink_to_fit();
}

big_integer::~big_integer() = default;

big_integer &big_integer::operator=(const big_integer &other) = default;

size_t big_integer::size() const {
    return data.size();
}

uint32_t &big_integer::operator[](const size_t i) {
    return data[i];
}

const uint32_t &big_integer::operator[](const size_t i) const {
    return data[i];
}

uint32_t big_integer::get_kth(const size_t k) const {
    return (k < size() ? data[k] : 0);
}

void big_integer::fill_back(const size_t n, const uint32_t value) {
    data.insert(data.end(), n, value);
}

uint32_t big_integer::low32_bits(const uint64_t a) {
    return static_cast<uint32_t>(UINT32_MAX & a);
}


uint32_t big_integer::high32_bits(const uint64_t a) {
    return (uint32_t) (a >> 32u);
}

big_integer &big_integer::operator+=(const big_integer &rhs) {
    if (sign && !rhs.sign) {
        return *this = rhs - (-*this);
    } else if (!sign && rhs.sign) {
        return *this -= -rhs;
    }  //  свел задачу к a + b, где a и b одного знака
    bool carry = false;
    if (rhs.size() > size()) {
        fill_back(rhs.size() - size(), 0);
    }
    for (size_t i = 0; i < size(); ++i) {
        const auto sum = static_cast<uint64_t>(data[i]) + rhs.get_kth(i) + carry;
        data[i] = low32_bits(sum);
        carry = high32_bits(sum);
    }
    if (carry) {
        fill_back(1, carry);
    }
    return *this;
}

big_integer &big_integer::operator-=(const big_integer &rhs) {
    if (sign && !rhs.sign) {
        return *this = -(rhs - *this);
    } else if (!sign && rhs.sign) {
        return *this += -rhs;
    } else if (sign && rhs.sign) {
        return *this = -((-*this) -= (-rhs));
    } else if (*this < rhs) {
        return *this = -(rhs - *this);
    }  //  свел задачу к a - b, где a >= 0, b >= 0, a >= b
    bool borrow = false;
    for (size_t i = 0; i < rhs.size() || borrow; ++i) {
        const auto sub = static_cast<int64_t>(data[i]) - rhs.get_kth(i) - borrow;
        borrow = sub < 0;
        data[i] = static_cast<uint32_t>(sub + (borrow ? BASE : 0));
    }
    shrink_to_fit();
    return *this;
}

size_t big_integer::bit_count(const uint32_t a) {
    return __builtin_popcount(a);
}

//  На степень двойки делить и умножать можно с помощью сдвигов.
//  Эти тесты не ускоряются, но для очень больших чисел оптимизация полезна
uint32_t big_integer::count() const {
    uint32_t ans = 0;
    for (const uint32_t digit : data) {
        ans += bit_count(digit);
    }
    return ans;
}

///  pre: *this is the power of 2
uint32_t big_integer::clear_log2() const {
    uint32_t skipped = 0;
    for (const uint32_t digit : data) {
        if (bit_count(digit) == 1) {
            return (uint32_t) (skipped + log2(digit));
        }
        skipped += 32;
    }
    throw std::runtime_error("pre-condition is not followed");
}

big_integer &big_integer::operator*=(const big_integer &rhs) {
    if (!sign && count() == 1) {
        return *this = rhs << clear_log2();
    } else if (!rhs.sign && rhs.count() == 1) {
        return *this <<= rhs.clear_log2();
    }
    big_integer ans;
    ans.sign = sign ^ rhs.sign;
    ans.fill_back(size() + rhs.size(), 0);
    for (size_t i = 0; i < size(); ++i) {
        uint32_t carry = 0;
        for (size_t j = 0; j < rhs.size() || carry; ++j) {
            const auto additive = static_cast<uint64_t>(data[i]) *
                    rhs.get_kth(j) + carry + ans[i + j];
            ans[i + j] = low32_bits(additive);
            carry = high32_bits(additive);
        }
    }
    ans.shrink_to_fit();
    return *this = ans;
}

std::pair<big_integer, uint32_t> big_integer::short_div(const big_integer &a, const uint32_t b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    uint64_t carry = 0;
    big_integer ans(a);
    for (ptrdiff_t i = ans.size() - 1; i >= 0; --i) {
        const auto dividend = static_cast<uint64_t>(ans[i]) + carry * BASE;
        ans[i] = low32_bits(dividend / b);
        carry = dividend % b;
    }
    ans.shrink_to_fit();
    return {ans, carry};
}

uint32_t big_integer::trial(const uint64_t k, const uint64_t m, const big_integer &d) const {
    const auto r3 = (static_cast<uint128_t>(data[(uint32_t) (k + m)]) * BASE +
            data[(uint32_t) (k + m - 1)]) * BASE + data[(uint32_t) (k + m - 2)];
    const uint64_t d2 = (static_cast<uint64_t>(d[(uint32_t) (m - 1)]) << 32u)
            + d[(uint32_t) (m - 2)];
    return low32_bits(std::min(r3 / d2, static_cast<uint128_t>(BASE - 1)));
}

bool big_integer::smaller(const big_integer &dq, const uint64_t k, const uint64_t m) const {
    uint64_t i = m, j = 0;
    while (i != j) {
        data[(uint32_t) (i + k)] == dq[(uint32_t) i] ? --i : j = i;
    }
    return data[(uint32_t) (i + k)] < dq[(uint32_t) i];
}

void big_integer::difference(const big_integer &dq, const uint64_t k, const uint64_t m) {
    uint64_t borrow = 0;
    for (size_t i = 0; i <= m; ++i) {
        const uint64_t diff = static_cast<uint64_t>(
                data[(uint32_t)(i + k)]) - dq[(uint32_t) i] - borrow + BASE;
        data[(uint32_t) (i + k)] = low32_bits(diff);
        borrow = 1 - high32_bits(diff);
    }
}

big_integer &big_integer::operator/=(const big_integer &rhs) {
    if (size() < rhs.size()) {
        return *this = 0;
    } else if (rhs.size() == 1) {
        const auto ans = big_integer::short_div(*this, rhs[0]);
        return *this = rhs.sign ? -ans.first : ans.first;
    } else if (!rhs.sign && rhs.count() == 1) {
        return *this >>= rhs.clear_log2();
    }
    const size_t n = size(), m = rhs.size();
    const uint64_t f = BASE / (static_cast<uint64_t>(rhs[m - 1]) + 1);
    big_integer q, r = (*this) * (int) f, d = rhs * (int) f;
    q.sign = sign ^ rhs.sign;
    q.fill_back(n - m + 1, 0);
    r.sign = d.sign = false;
    r.fill_back(1, 0);
    for (ptrdiff_t k = n - m; k >= 0; --k) {
        uint32_t qt = r.trial(static_cast<uint64_t>(k), m, d);
        auto dq = big_integer(qt) * d;
        dq.fill_back(m + 1, 0);
        if (r.smaller(dq, static_cast<uint64_t>(k), m)) {
            qt--;
            dq = d * qt;
        }
        q[k] = qt;
        r.difference(dq, static_cast<uint64_t>(k), m);
    }
    q.shrink_to_fit();
    return *this = q;
}

big_integer &big_integer::operator%=(const big_integer &rhs) {
    return *this -= (*this / rhs) * rhs;
}

void big_integer::to_additional_code(const size_t n_digits) {
    fill_back(n_digits - size(), 0);
    if (sign) {
        sign = false;
        for (uint32_t &digit : data) {
            digit = ~digit;
        }
        *this += 1;
    }
}

big_integer &
big_integer::bitwise_operation(const big_integer &rhs, const func &f) {
    big_integer ans(*this), tmp_rhs(rhs);
    const size_t max_size = std::max(size(), rhs.size());
    ans.to_additional_code(max_size);
    tmp_rhs.to_additional_code(max_size);
    ans.sign = f(sign, rhs.sign);
    for (size_t i = 0; i < max_size; ++i) {
        ans[i] = f(ans[i], tmp_rhs[i]);
    }
    if (ans.sign) {
        ans.to_additional_code(max_size);
        ans.sign = true;
    }
    ans.shrink_to_fit();
    return *this = ans;
}

big_integer &big_integer::operator&=(const big_integer &rhs) {
    return *this = bitwise_operation(rhs, [](uint32_t a, uint32_t b) { return a & b; });
}

big_integer &big_integer::operator|=(const big_integer &rhs) {
    return *this = bitwise_operation(rhs, [](uint32_t a, uint32_t b) { return a | b; });
}

big_integer &big_integer::operator^=(const big_integer &rhs) {
    return *this = bitwise_operation(rhs, [](uint32_t a, uint32_t b) { return a ^ b; });
}

big_integer &big_integer::operator<<=(const int b) {
    if (b < 0) {
        return *this >>= (-b);
    }
    const auto n_added = static_cast<size_t>(b / 32);
    fill_back(n_added, 0);
    for (ptrdiff_t i = size() - n_added - 1; i >= 0; --i) {
        std::swap(data[i + n_added], data[i]);
    }
    const auto shift = static_cast<uint32_t>(b % 32);
    uint64_t carry = 0;
    for (size_t i = n_added; i < size(); ++i) {
        const uint64_t tmp = (static_cast<uint64_t>(data[i]) << shift) | carry;
        data[i] = low32_bits(tmp);
        carry = high32_bits(tmp);
    }
    fill_back(1, (uint32_t) carry);
    shrink_to_fit();
    return *this;
}

big_integer &big_integer::operator>>=(const int b) {
    if (b < 0) {
        return *this <<= (-b);
    }
    const auto n_deleted = static_cast<size_t>(b / 32);
    for (size_t i = 0; i < size() - n_deleted; ++i) {
        data[i] = data[i + n_deleted];
    }
    for (size_t i = 0; i < n_deleted; ++i) {
        data.pop_back();
    }
    const auto shift = static_cast<uint32_t>(b % 32);
    uint32_t carry = 0;
    for (ptrdiff_t i = size() - 1; i >= 0; --i) {
        const auto tmp = static_cast<uint64_t>(data[i]) << (32 - shift);
        data[i] = high32_bits(tmp) | carry;
        carry = low32_bits(tmp);
    }
    shrink_to_fit();
    return sign ? --(*this) : (*this);
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    big_integer a(*this);
    if (a != 0) {
        a.sign ^= true;
    }
    return a;
}

big_integer big_integer::operator~() const {
    return -(*this) - 1;
}

big_integer &big_integer::operator++() {  // ++a
    return (*this) += 1;
}

big_integer big_integer::operator++(int) {  // a++
    big_integer a(*this);
    (*this) += 1;
    return a;
}

big_integer &big_integer::operator--() {
    return (*this) -= 1;
}

big_integer big_integer::operator--(int) {
    big_integer a(*this);
    (*this) -= 1;
    return a;
}

big_integer operator+(big_integer a, const big_integer &b) {
    return a += b;
}

big_integer operator-(big_integer a, const big_integer &b) {
    return a -= b;
}

big_integer operator*(big_integer a, const big_integer &b) {
    return a *= b;
}

big_integer operator/(big_integer a, const big_integer &b) {
    return a /= b;
}

big_integer operator%(big_integer a, const big_integer &b) {
    return a %= b;
}

big_integer operator&(big_integer a, const big_integer &b) {
    return a &= b;
}

big_integer operator|(big_integer a, const big_integer &b) {
    return a |= b;
}

big_integer operator^(big_integer a, const big_integer &b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, const int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, const int b) {
    return a >>= b;
}

bool operator==(const big_integer &a, const big_integer &b) {
    return (a.sign == b.sign && a.data == b.data);
}

bool operator!=(const big_integer &a, const big_integer &b) {
    return !(a == b);
}

bool operator<(const big_integer &a, const big_integer &b) {
    if (a.sign != b.sign) {
        return a.sign;
    }
    if (a.size() != b.size()) {
        return (a.size() < b.size()) ^ a.sign;
    }
    for (ptrdiff_t i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) {
            return (a[i] < b[i]) ^ a.sign;
        }
    }
    return false;
}

bool operator>(const big_integer &a, const big_integer &b) {
    return !(a <= b);
}

bool operator<=(const big_integer &a, const big_integer &b) {
    return (a < b) || (a == b);
}

bool operator>=(const big_integer &a, const big_integer &b) {
    return !(a < b);
}

std::string to_string(const big_integer &a) {
    if (a == 0) {
        return "0";
    }
    std::string str;
    big_integer tmp(a);
    while (tmp != 0) {
        const auto division = big_integer::short_div(tmp, 10);
        str += static_cast<char>('0' + division.second);
        tmp = division.first;
    }
    if (a.sign) {
        str += '-';
    }
    reverse(str.begin(), str.end());
    return str;
}

std::ostream &operator<<(std::ostream &s, const big_integer &a) {
    s << to_string(a);
    return s;
}

void big_integer::shrink_to_fit() {
    while (size() > 1 && data.back() == 0) {
        data.pop_back();
    }
    if (size() == 1 && data.back() == 0) {
        sign = false;
    }
}

const int ALPHABET_SIZE = 100;
const int MAX_SIZE = 101;
map<char, int> char_to_id;

struct Node {
    int next[ALPHABET_SIZE]{};
    bool term{};
    int link{};
};

string alph;
Node nodes[MAX_SIZE];
int sz = 1;

void add_string(string &s) {
    int id = 0;
    for (char c : s) {
        int &next_id = nodes[id].next[char_to_id[c]];
        if (next_id == 0) {
            next_id = sz;
            nodes[sz++] = Node();
        }
        id = next_id;
    }
    nodes[id].term = true;
}

void add_links() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        Node &node = nodes[v];
        int u = node.link;
        Node &link_node = nodes[u];
        for (char c : alph) {
            int id = char_to_id[c];
            if (node.next[id] != 0) {
                nodes[node.next[id]].link = (v == 0 ? 0 : link_node.next[id]);
                q.push(node.next[id]);
            } else {
                node.next[id] = link_node.next[id];
            }
        }
    }
}

int main() {
    fastio;
    int n, m, p;
    cin >> n >> m >> p;
    vector<string> bad;
    cin >> alph;
    for (int i = 0; i < (int) alph.size(); ++i) {
        char_to_id[alph[i]] = i;
    }
    for (int i = 0; i < p; ++i) {
        string s;
        cin >> s;
        bad.push_back(s);
    }
    bool changes = true;
    while (changes) {
        changes = false;
        for (int i = 0; i < (int) bad.size(); ++i) {
            string s = bad[i];
            bool substr = false;
            for (int j = 0; j < (int) bad.size(); ++j) {
                if (i == j) {
                    continue;
                }
                string t = bad[j];
                for (int l = 0; l + t.size() <= s.size(); ++l) {
                    if (t == s.substr(l, t.size())) {
                        substr = true;
                        break;
                    }
                }
                if (substr) {
                    break;
                }
            }
            if (substr) {
                bad.erase(bad.begin() + i);
                changes = true;
                break;
            }
        }
    }
    for (string &s : bad) {
        add_string(s);
    }
    add_links();
    vector<vector<int>> nxt(sz, vector<int> (n, -1));
    for (int u = 0; u < sz; ++u) {
        Node &node = nodes[u];
        if (node.term) {
            continue;
        }
        for (char c : alph) {
            int id = char_to_id[c];
            int v = node.next[id];
            if (v != -1 && !nodes[v].term) {
                nxt[u][id] = v;
            }
        }
    }
    vector<vector<big_integer>> dp(m + 1, vector<big_integer> (sz, 0));
    dp[0][0] = 1;
    for (int len = 1; len <= m; ++len) {
        for (int u = 0; u < sz; ++u) {
            if (!nodes[u].term) {
                for (char c : alph) {
                    int id = char_to_id[c];
                    int v = nxt[u][id];
                    if (v != -1) {
                        dp[len][v] += dp[len - 1][u];
                    }
                }
            }
        }
    }
    big_integer ans = 0;
    for (int u = 0; u < sz; ++u) {
        if (!nodes[u].term) {
            ans += dp[m][u];
        }
    }
    cout << ans;
    return 0;
}
