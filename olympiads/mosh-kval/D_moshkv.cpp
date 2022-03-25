
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
//#pragma GCC optimize("unroll-loops")

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


int32_t main() {
    fast_io
    freopen("../assets/mosh/mosh_d2.txt", "r", stdin);
    freopen("../assets/test_ans/mosh_d2_ans.txt", "w", stdout);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vi d(n);
        for (auto &e : d)
            cin >> e;
        vvi p(m, vi(n));
        for (auto &r : p)
            for (auto &e : r)
                cin >> e;

        ll ans = 8e18;
        vi vans(m, -1);
        for (ui mask = 1; mask < (1u << n); ++mask) {
            vi curr(m, -1);
            ll csum = 0;
            for (int i = 0; i < n; ++i) {
                if ((mask & (1u << i)) == 0)
                    continue;
                csum += d[i];
                for (int j = 0; j < m; ++j) {
                    if (curr[j] == -1 || p[j][i] < p[j][curr[j]])
                        curr[j] = i;
                }
            }
            for (int i = 0; i < m; ++i)
                csum += p[i][curr[i]];
            if (csum < ans) {
                ans = csum;
                vans = curr;
            }
        }
        cout << ans << '\n';
        for (auto &e : vans)
            cout << e + 1 << ' ';
        cout << '\n';
    }
}