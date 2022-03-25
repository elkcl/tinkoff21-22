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

void fact(ll n, unordered_map<int, int> &m) {
    while (n % 2 == 0) {
        ++m[2];
        n /= 2;
    }
    int f = 3;
    while (f * f <= n) {
        if (n % f == 0) {
            ++m[f];
            n /= f;
        } else {
            f += 2;
        }
    }
    if (n != 1) {
        ++m[n];
    }
}


int32_t main() {
    fast_io

    ll b, n, m;
    cin >> b >> n >> m;
    if (m == 1) {
        cout << "0\n";
        return 0;
    }
    ll lm = static_cast<ll>(floor(log2(m)/log2(b))) + 1;
    if (lm > n) {
        if (n == 1) {
            cout << "1\n";
            return 0;
        }
        cout << "0\n";
        return 0;
    }

    unordered_map<int, int> bf, mf;
    fact(b, bf);
    fact(m, mf);
    int st = 0;
    for (auto [k, v] : mf) {
        if (bf.find(k) == bf.end()) {
            if (b == 2 && n > 1) {
                cout << n - 1 << '\n';
                return 0;
            }
            cout << n << '\n';
            return 0;
        }
        st = max(st, v / bf[k] + (v % bf[k] != 0));
    }
    cout << st << '\n';
}