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

const ll M = 998'244'353;

int32_t main() {
    fast_io

    int n;
    cin >> n;
    vll a(n);
    for (auto &e : a)
        cin >> e;
    vll dp(n, 0);
    vll dpi(n, 0);
    dp[0] = dpi[0] = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] >= a[i - 1]) {
            dp[i] += dp[i - 1];
        }
        if (a[i] >= -a[i - 1]) {
            dp[i] += dpi[i - 1];
        }
        dp[i] %= M;
        if (-a[i] >= a[i - 1]) {
            dpi[i] += dp[i - 1];
        }
        if (-a[i] >= -a[i - 1]) {
            dpi[i] += dpi[i - 1];
        }
        dpi[i] %= M;
    }
    cout << (dp.back() + dpi.back()) % M << '\n';
}