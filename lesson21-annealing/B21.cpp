#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
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
#define endl '\n'

const int n = 10;
const int m = 10;
const int k = 10000000;

using table = array<array<char, m>, n>;

int f(const table &t) {
    int ans = 0;
    for (int x1 = 0; x1 < n - 1; ++x1) {
        for (int x2 = x1 + 1; x2 < n; ++x2) {
            for (int y1 = 0; y1 < m - 1; ++y1) {
                for (int y2 = y1 + 1; y2 < m; ++y2) {
                    if (t[x1][y1] == t[x2][y1] && t[x1][y1] == t[x1][y2] && t[x1][y1] == t[x2][y2])
                        ++ans;
                }
            }
        }
    }
    return ans;
}

signed main() {
    fast_io

    const int seed = 69;
    mt19937 gen(seed);
    table curr;
    uniform_int_distribution<char> dist_c(0, 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            curr[i][j] = dist_c(gen);
        }
    }
    int ans = f(curr);
    ld t = 1;
    uniform_int_distribution<int> dist_x(0, n - 1);
    uniform_int_distribution<int> dist_y(0, m - 1);
    uniform_int_distribution<char> dist_b(1, 2);
    uniform_real_distribution<ld> dist(0, 1);
    for (int i = 0; i < k && ans != 0; ++i) {
        t = 1 - static_cast<ld>(i) / k;
        int x = dist_x(gen);
        int y = dist_y(gen);
        char prev_c = curr[x][y];
        char c = static_cast<char>((prev_c + dist_b(gen)) % 3);
        curr[x][y] = c;
        int val = f(curr);
        if (val > ans && dist(gen) < 1 - exp((ans - val) / t)) {
            curr[x][y] = prev_c;
        } else {
            ans = val;
        }
    }

    cout << ans << endl;
    for (auto &r : curr) {
        for (auto e: r)
            cout << static_cast<int>(e) + 1 << ' ';
        cout << endl;
    }
}