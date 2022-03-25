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

struct ev {
    int l, r;
    ll x, y;
};

int32_t main() {
    fast_io

    int n;
    cin >> n;
    vll a(n);
    for (ll &e : a)
        cin >> e;
    for (int i = 0; i < n; ++i) {
        ll b;
        cin >> b;
        a[i] -= b;
    }
    int m;
    cin >> m;
    vector<ev> evs(m);
    for (auto &e : evs) {
        cin >> e.l >> e.r >> e.x >> e.y;
        --e.l, --e.r;
    }
    vi ans(n, -1);
    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (j < m && a[i] < 0) {
            if (i >= evs[j].l && i <= evs[j].r) {
                a[i] += evs[j].x + evs[j].y * (i - evs[j].l);
            }
            ++j;
        }
        if (a[i] >= 0)
            ans[i] = j;
    }

    for (int &e : ans)
        cout << e << ' ';
    cout << '\n';
}