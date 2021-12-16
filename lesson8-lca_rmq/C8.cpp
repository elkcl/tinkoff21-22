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

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;
using ld = long double;
using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct edge {
    int to, w;
};

void dfs(vector<vector<edge>> &g, vc &used, vvi &up, vi &tin, vi &tout, int logn, int &t, int v) {
    for (int i = 1; i < logn; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    tin[v] = t++;
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            up[to][0] = v;
            dfs(g, used, up, tin, tout, logn, t, to);
        }
    }
    tout[v] = t;
}

int main() {
    fast_io

    int n, q;
    cin >> n >> q;
    vector<vector<edge>> g(n);
    for (int i = 0; i < n; ++i) {
        int s, f, l;
        cin >> s >> f >> l;
        g[s-1].push_back({f-1, l});
        g[f-1].push_back({s-1, l});
    }

    vc used(n, false);
    int logn = static_cast<int>(floor(log2(n)) + 1);
    vvi up(n, vi(logn, 0));
    vi tin(n), tout(n);
    int t = 0;

    dfs(g, used, up, tin, tout, logn, t, 0);
}