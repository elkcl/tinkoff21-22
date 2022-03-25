#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
//#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <numeric>
#include <set>
#include <array>
#include <cassert>
#include <map>
#include <unordered_map>
#include <deque>
#include <stack>
#include <unordered_set>
#include <list>
#include <sstream>

//#define int int64_t

using namespace std;
using ll = int64_t;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = uint32_t;
using ull = uint64_t;
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct card {
    string s;
    int k;
};

int cton(char c) {
    if (c == '#')
        return 0;
    if (c == '$')
        return 1;
    if (c >= '0' && c <= '9')
        return c - '0' + 2;
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 12;
    return c - 'a' + 38;
}

char ntoc(int n) {
    if (n == 0)
        return '#';
    if (n == 1)
        return '$';
    if (n >= 2 && n <= 11)
        return static_cast<char>('0' + n - 2);
    if (n >= 12 && n <= 37)
        return static_cast<char>('A' + n - 12);
    return static_cast<char>('a' + n - 38);
}

void mhalf(card &c) {
    c.s.front() = ntoc(cton(c.s.front()) - 32);
}

void inc(card &c, int i = 0) {
    if (c.s[c.k - i - 1] == 'z') {
        c.s[c.k - i - 1] = '#';
        inc(c, i + 1);
    } else {
        c.s[c.k - i - 1] = ntoc(cton(c.s[c.k - i - 1]) + 1);
    }
}

void dbl(card &c, int i = 0, int carry = 0) {
    int res = cton(c.s[c.k - i - 1]) * 2 + carry;
    c.s[c.k - i - 1] = ntoc(res % 64);
    if (i != c.k - 1) {
        dbl(c, i + 1, res / 64);
    }
}

bool operator==(const card &a, const card &b) {
    return a.s == b.s;
}

bool operator<(const card &a, const card &b) {
    return a.s < b.s;
}

bool lhf(card &c) {
    return cton(c.s.front()) < 32;
}


int32_t main() {
    fast_io

    int k, m;
    cin >> k >> m;
    while (m--) {
        string x, y;
        cin >> x >> y;
        card curr{x, k};
        card goal{y, k};
        bool found = false;
        for (int i = 0; i < 6 * k; ++i) {
            if (curr == goal) {
                found = true;
                cout << i << '\n';
                break;
            }
            if (lhf(curr)) {
                dbl(curr);
            } else {
                mhalf(curr);
                dbl(curr);
                inc(curr);
            }
        }
        if (!found)
            cout << "-1\n";
    }
}