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

vector<vii> queries;
vi ans;
vvi g;
vi s;
vc used;
vi a;
vi col;

const int INF = 1e9;

int sizes(int v, int p) {
    s[v] = 1;
    for (int to : g[v])
        if (to != p && !used[to])
            s[v] += sizes(to, v);
    return s[v];
}

int centroid(int v, int p, int n) {
    for (int to : g[v])
        if (to != p && !used[to] && s[to] > n / 2)
            return centroid(to, v, n);
    return v;
}

void dfs1(int v, int p, int d, unordered_set<int> &cols) {
    if (cols.find(a[v]) != cols.end()) {
        col[a[v]] = min(col[a[v]], d);
    } else {
        col[a[v]] = d;
        cols.insert(a[v]);
    }
    for (int to : g[v])
        if (to != p && !used[to])
            dfs1(to, v, d + 1, cols);
}

void dfs2(int v, int p, int d, unordered_set<int> &cols) {
    for (auto [co, id] : queries[v])
        if (cols.find(co) != cols.end())
            ans[id] = min(ans[id], d + col[co]);
    for (int to : g[v])
        if (to != p && !used[to])
            dfs2(to, v, d + 1, cols);
}

void solve(int v) {
    unordered_set<int> cols;
    /*cols.insert(a[v]);
    col[a[v]] = 0;*/
    sizes(v, -1);
    dfs1(v, -1, 0, cols);
    dfs2(v, -1, 0, cols);
    /*for (int to : g[v])
        if (!used[to])
            dfs1(to, v, 1, cols);
    for (int to : g[v])
        if (!used[to])
            dfs2(to, v, 1, cols);*/

    used[v] = true;
    for (int to : g[v])
        if (!used[to])
            solve(centroid(to, v, s[to]));
}

int main() {
    fast_io

    int n;
    cin >> n;
    g.resize(n);
    col.resize(n);
    queries.resize(n);
    s.resize(n);
    used.resize(n);
    a.resize(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    for (int &e : a)
        cin >> e;
    int q;
    cin >> q;
    ans.resize(q, INF);
    for (int i = 0; i < q; ++i) {
        int v, c;
        cin >> v >> c;
        queries[v].push_back({c, i});
        /*if (a[v] == c)
            ans[i] = 0;*/
    }

    sizes(0, -1);
    solve(centroid(0, -1, n));
    for (int i = 0; i < q; ++i) {
        if (ans[i] == INF)
            cout << "-1 ";
        else
            cout << ans[i] << ' ';
    }
    cout << '\n';
}