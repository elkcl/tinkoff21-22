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

int32_t main() {
    fast_io

    int n, s;
    cin >> n >> s;
    vi a(n), b(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    iota(all(p), 0);
    ll ans = 1e9;
    int len = -1;
    vi pans;
    do {
        ll curr = s;
        int i = 0;
        while (i < n && curr >= a[p[i]]) {
            curr += b[p[i]];
            ++i;
        }
        if (curr < ans) {
            ans = curr;
            pans = p;
            len = i;
        }
    } while (next_permutation(all(p)));
    cout << ans << ' ' << len << '\n';
    for (int i = 0; i < len; ++i) {
        cout << pans[i] + 1 << ' ';
    }
    cout << '\n';
}