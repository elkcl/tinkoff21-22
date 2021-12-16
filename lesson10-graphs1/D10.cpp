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

bool ans = false;

void dfs(vvi &g, vc &used, int v) {
    used[v] = 1;
    for (auto to : g[v]) {
        if (used[to] == 1)
            ans = true;
        if (used[to] == 0)
            dfs(g, used, to);
    }
    used[v] = 2;
}

int main() {
    fast_io

    int n;
    cin >> n;
    vvi g(n);
    for (int i = 0; i < n - 1; ++i) {
        string r;
        cin >> r;
        for (int j = 0; j < n - i - 1; ++j) {
            if (r[j] == 'B') {
                g[i].push_back(i + j + 1);
            } else {
                g[i + j + 1].push_back(i);
            }
        }
    }

    vc used(n, 0);
    for (int v = 0; v < n; ++v)
        if (used[v] == 0)
            dfs(g, used, v);
    if (ans) {
        cout << "YES\n";
    } else {
        /*for (int i = 0; i < 10000; ++i)
            cerr << i << '\n';*/
        cout << "NO\n";
    }
}