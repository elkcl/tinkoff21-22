#ifndef ONPC
#pragma GCC optimize("O3")

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

void dfs1(vvi &g, vc &used, vi &top, int v) {
    used[v] = true;
    for (auto to : g[v])
        if (!used[to])
            dfs1(g, used, top, to);
    top.push_back(v);
}

void dfs2(vvi &t, vi &comps, int &curr, int v) {
    comps[v] = curr;
    for (auto to : t[v])
        if (comps[to] == -1)
            dfs2(t, comps, curr, to);
}

int main() {
    fast_io

    int n, m;
    while (cin >> n >> m) {
        if (n == 0)
            continue;
        if (m == 0) {
            while (n--)
                cout << 0;
            cout << '\n';
            continue;
        }

        vvi g(2 * n), t(2 * n);
        for (int i = 0; i < m; ++i) {
            int i1, i2;
            bool e1, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            i1 = (2 * i1) ^ e1 ^ 1;
            i2 = (2 * i2) ^ e2 ^ 1;
            g[i1 ^ 1].push_back(i2);
            t[i2].push_back(i1 ^ 1);
            g[i2 ^ 1].push_back(i1);
            t[i1].push_back(i2 ^ 1);
        }

        vc used(2 * n, false);
        vi top;
        for (int v = 0; v < 2 * n; ++v)
            if (!used[v])
                dfs1(g, used, top, v);
        reverse(all(top));

        vi comps(2 * n, -1);
        int curr = 0;
        for (int v : top) {
            if (comps[v] == -1) {
                dfs2(t, comps, curr, v);
                ++curr;
            }
        }

        vi ans(n);
        for (int i = 0; i < 2 * n; i += 2)
            ans[i / 2] = comps[i] > comps[i ^ 1];
        for (int e : ans)
            cout << e;
        cout << '\n';
    }
}