#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2")
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
//#include <optional>
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
//using i128 = __int128;

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

const int INF = 1.5e9;

ll glob_tl = 0;

#define WA cout << "-1\n"; return 0;
#define TL for (glob_tl = 0; glob_tl < 4e18; ++glob_tl);
#define RT return 1;

int main() {
    fast_io

    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    vector<vector<edge>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            g[i].push_back({j, abs(i - j) + abs(a[i] - a[j])});
        }
    }
    //WA
    vvi dp(1u << n, vi(n, INF));
    for (int i = 0; i < n; ++i)
        dp[1u << i][i] = 0;
    //WA
    for (ui mask = 1; mask < (1u << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if ((mask & (1u << i)) == 0)
                continue;
            for (auto &ed : g[i]) {
                if ((mask & (1u << ed.to)) == 0)
                    continue;
                /*if (dp[mask ^ (1u << i)][ed.to] == INF) {
                    continue;
                }*/
                dp[mask][i] = min(dp[mask][i], dp[mask ^ (1u << i)][ed.to] + ed.w);
            }
        }
    }
    //WA
    vi path;
    path.reserve(n);
    ui mask = (1u << n) - 1;
    int last = -1;
    int minlen = INF;
    for (int i = 0; i < n; ++i) {
        if (dp[mask][i] + i + a[i] < minlen) {
            minlen = dp[mask][i] + i + a[i];
            last = i;
        }
    }
    /*if (last == -1) {
        cout << "-1\n";
        return 0;
    }*/
#ifdef ONPC
    cout << minlen << '\n';
#endif
    while (mask != 0) {
        path.push_back(last);
        mask ^= 1u << last;
        for (auto &ed : g[last]) {
            if ((mask & (1u << ed.to)) == 0)
                continue;
            if (dp[mask ^ (1u << last)][last] - ed.w == dp[mask][ed.to]) {
                //mask ^= 1u << last;
                last = ed.to;
                break;
            }
        }
    }
    //reverse(all(path));
    /*if (path.size() != n + 1) {
        for (; glob_tl < 4e18; ++glob_tl)
            ;
    }*/

    for (int j = 0; j < path[0]; ++j)
        cout << 'R';
    for (int j = 0; j < a[path[0]]; ++j)
        cout << 'r';
    for (int i = 1; i < n; ++i) {
        ii a1 = {path[i - 1], a[path[i - 1]]};
        ii a2 = {path[i], a[path[i]]};
        if (a1.first < a2.first) {
            for (int j = 0; j < a2.first - a1.first; ++j)
                cout << 'R';
        } else {
            for (int j = 0; j < a1.first - a2.first; ++j)
                cout << 'L';
        }
        if (a1.second < a2.second) {
            for (int j = 0; j < a2.second - a1.second; ++j)
                cout << 'r';
        } else {
            for (int j = 0; j < a1.second - a2.second; ++j)
                cout << 'l';
        }
    }
    cout << '\n';
}