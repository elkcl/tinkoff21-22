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
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif



int32_t main() {
    fast_io

    int n;
    cin >> n;
    vector<ui> a(n);
    for (ui &e : a)
        cin >> e;
    sort(all(a));
    vector<ui> s(a);
    int m = unique(all(s)) - s.begin();
    s.resize(m);
    vi cnts(m, 0);
    int p = 0;
    for (int i = 0; i < m; ++i) {
        while (p < n && a[p] == s[i])
            ++p, ++cnts[i];
    }
    vll ans(m, 0);
    for (int i = 2; i < m; ++i) {
        for (int j = 1; j < i; ++j) {
            ui x = s[i] ^ s[j];
            if (x >= s[j])
                continue;
            auto r = lower_bound(all(a), s[j]);
            ans[i] += 1ll * cnts[i] * cnts[j] * (upper_bound(a.begin(), r, x) - lower_bound(a.begin(), r, x));
        }
    }

    cout << accumulate(all(ans), 0ll) << '\n';
}