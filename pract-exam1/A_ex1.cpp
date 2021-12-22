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

struct vertex {
    int w, l, r;
};

ii dfs(int v, vector<vertex> &g, int &ans) {
    if (g[v].w != -1) {
        return {g[v].w, g[v].w};
    }
    ii l = dfs(g[v].l, g, ans);
    ii r = dfs(g[v].r, g, ans);
    if (l == pair{1, 0} || r == pair{1, 0})
        return {1, 0};
    if (l.second < r.first)
        return {l.first, r.second};
    if (r.second < l.first) {
        ++ans;
        return {r.first, l.second};
    }
    return {1, 0};
}

int main() {
    fast_io

    int t;
    cin >> t;
    while (t--) {
        int ans = 0;
        int n;
        cin >> n;
        vector<vertex> g(n);
        for (int i = 0; i < n; ++i) {
            int l, r;
            cin >> l >> r;
            if (l == -1) {
                g[i].w = r;
                g[i].l = g[i].r = -1;
            } else {
                g[i].w = -1;
                g[i].l = l - 1;
                g[i].r = r - 1;
            }
        }
        ii res = dfs(0, g, ans);
        if (res == pair{1, 0}) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    }
}