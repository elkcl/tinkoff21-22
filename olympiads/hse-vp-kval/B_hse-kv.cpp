#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
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

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct edge {
    int u;
    ll w;
};

const ll INF = 1e18;

int main() {
    fast_io

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s, --t;
    vector<vector<edge>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    vll d(n, INF);
    vi gaz(n, 1);
    d[s] = 0;
    gaz[s] = 0;
    vi p(n, -1);
    set<tuple<ll, int, int>> unused;
    for (int v = 0; v < n; ++v)
        unused.insert({d[v], gaz[v], v});
    while (!unused.empty()) {
        ll vd;
        int gv;
        int v;
        tie(vd, gv, v) = *unused.begin();
        unused.erase(unused.begin());
        for (auto e : g[v]) {
            if (d[e.u] > d[v] + e.w) {
                unused.erase({d[e.u], gaz[e.u], e.u});
                d[e.u] = d[v] + e.w;
                if (e.u == t)
                    gaz[e.u] = min(gaz[e.u], gaz[v]);
                else
                    gaz[e.u] = min(gaz[e.u], gaz[v] - 1);
                unused.insert({d[e.u], gaz[e.u], e.u});
                p[e.u] = v;
            }
            else if (d[e.u] == d[v] + e.w && gaz[e.u] > gaz[v] - 1) {
                unused.erase({d[e.u], gaz[e.u], e.u});
                if (e.u == t)
                    gaz[e.u] = min(gaz[e.u], gaz[v]);
                else
                    gaz[e.u] = min(gaz[e.u], gaz[v] - 1);
                unused.insert({d[e.u], gaz[e.u], e.u});
                p[e.u] = v;
            }
        }
    }
    vi path;
    for (int v = t; v != -1; v = p[v])
        path.push_back(v);
    reverse(all(path));

    cout << d[t] << '\n';
    cout << path.size() - 2 << '\n';
    for (int i = 1; i < path.size() - 1; ++i)
        cout << path[i] + 1 << ' ';
    cout << '\n';
}