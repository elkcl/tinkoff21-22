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

void dfs1(vvi &g, vc &used, vvi &up, vi &tin, vi &tout, int logn, int &t, int v) {
    for (int i = 1; i < logn; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    tin[v] = t++;
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            up[to][0] = v;
            dfs1(g, used, up, tin, tout, logn, t, to);
        }
    }
    tout[v] = t;
}

void dfs2(vvi &g, vc &used, vi &s, vi &res, int curr, int v) {
    used[v] = true;
    res[v] += s[v] + curr;
    for (int to : g[v])
        if (!used[to])
            dfs2(g, used, s, res, curr + s[v], to);
}

int main() {
    fast_io

    int n;
    cin >> n;
    vvi g(n);
    for (int i = 0; i < n - 1; ++i) {
        int s, f;
        cin >> s >> f;
        g[s-1].push_back(f-1);
        g[f-1].push_back(s-1);
    }

    vc used(n, false);
    int logn = static_cast<int>(ceil(log2(n))) + 1;
    vvi up(n, vi(logn, 0));
    vi tin(n), tout(n);
    int t = 0;
    dfs1(g, used, up, tin, tout, logn, t, 0);
    auto anc = [&tin, &tout](int u, int v) {
        return tin[u] <= tin[v] && tin[v] < tout[u];
    };

    vi s(n, 0);
    int m;
    cin >> m;
    for (int q = 0; q < m; ++q) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        if (anc(b, a))
            swap(a, b);
        if (anc(a, b)) {
            ++s[b];
            ++s[0];
            for (int i = logn - 1; i >= 0; --i)
                if (!anc(up[b][i], a))
                    b = up[b][i];
            --s[b];
        } else {
            ++s[a];
            ++s[b];
        }
    }

    vi res(n, 0);
    used.resize(n, false);
    dfs2(g, used, s, res, 0, 0);
    int ans = *max_element(all(res));
    cout << ans << '\n';
}