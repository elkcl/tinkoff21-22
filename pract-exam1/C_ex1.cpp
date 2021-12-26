#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2")
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
#include <optional>
#include <cassert>
#include <map>
#include <unordered_map>
#include <deque>
#include <stack>
#include <unordered_set>

//#define int int64_t

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
//using ui = unsigned int;
using ld = long double;
using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

int get(int v) {
    cout << "? " << v + 1 << endl;
    int to;
    cin >> to;
    if (to == -2)
        exit(0);
    if (to == -1)
        return -1;
    return to - 1;
}

void dfs(vc &used, vi &h, vi &d, vii &bridges, int v, int p = -1) {
    used[v] = true;
    if (p == -1)
        d[v] = h[v] = 0;
    else
        d[v] = h[v] = h[p] + 1;
    for (int to = get(v); to != -1; to = get(v)) {
        if (used[to]) {
            d[v] = min(d[v], h[to]);
        } else {
            dfs(used, h, d, bridges, to, v);
            d[v] = min(d[v], d[to]);
            if (h[v] < d[to])
                bridges.push_back({v, to});
        }
    }
}

int32_t main() {
    fast_io

    int n, m;
    cin >> n >> m;
    if (m > 2 * n - 2) {
        cout << "! No\n";
        return 0;
    }

    vc used(n, false);
    vi h(n), d(n);
    vii bridges;
    for (int v = 0; v < n; ++v)
        if (!used[v])
            dfs(used, h, d, bridges, v);

    int x = bridges.size();
    if (2 * x < m) {
        cout << "! No" << endl;
    } else {
        cout << "! Yes" << endl;
        for (int i = 0; 2 * i < m; ++i)
            cout << bridges[i].first + 1 << ' ' << bridges[i].second + 1 << endl;
    }
}