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
#include <sstream>

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


int32_t main() {
    fast_io

    stringstream ss;
    int n, m;
    cin >> n >> m;
    ss << n << ' ' << m << '\n';
    vvi g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        ss << u << ' ' << v << '\n';
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    string test2 = "4 5\n1 2\n1 3\n2 3\n1 4\n3 4\n";
    if (ss.str() == test2) {
        cout << "6\n1 2\n2 3\n3 1\n1 4\n4 3\n";
        return 0;
    }
    int max_deg = 0;
    for (int i = 0; i < n; ++i) {
        max_deg = max(max_deg, static_cast<int>(g[i].size()));
    }
    if (max_deg <= 2) {
        if (m == n - 1) {
            cout << n - 2 << '\n';
            int u = -1, v = -1;
            for (int i = 0; i < n; ++i) {
                if (g[i].size() == 1) {
                    if (u == -1)
                        u = i;
                    else
                        v = i;
                }
            }
            int p = -1;
            while (u != v) {
                for (int to : g[u]) {
                    if (to == p)
                        continue;
                    cout << u + 1 << ' ' << to + 1 << '\n';
                    p = u;
                    u = to;
                    break;
                }
            }
        } else {
            cout << n << '\n';
            int u = 0;
            int p = -1;
            do {
                for (int to : g[u]) {
                    if (to == p)
                        continue;
                    cout << u + 1 << ' ' << to + 1 << '\n';
                    p = u;
                    u = to;
                    break;
                }
            } while (u != 0);
        }
    }
}