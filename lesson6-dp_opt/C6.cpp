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

const int INF = 1.9e9;

int main() {
    fast_io

    int n;
    while (cin >> n) {
        vi f(n);
        for (int &e : f)
            cin >> e;
        vi sf(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            sf[i] = sf[i - 1] + f[i - 1];
        vvi dp(n + 1, vi(n + 1, INF));
        vvi opt(n + 1, vi(n + 1));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 0;
            dp[i][i + 1] = 0;
            opt[i][i + 1] = i;
        }
        dp[n][n] = 0;
        for (int len = 2; len <= n; ++len) {
            for (int i = 0, j = len; i <= n - len; ++i, ++j) {
                int sum = sf[j] - sf[i];
                for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; ++k) {
                    int val = dp[i][k] + dp[k + 1][j] + sum - f[k];
                    if (val < dp[i][j]) {
                        dp[i][j] = val;
                        opt[i][j] = k;
                    }
                }
            }
        }
        cout << dp[0][n] << '\n';
    }
}