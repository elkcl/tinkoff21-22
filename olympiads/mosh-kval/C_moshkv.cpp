
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
    freopen("../assets/mosh/mosh_c2.txt", "r", stdin);
    freopen("../assets/test_ans/mosh_c2_ans.txt", "w", stdout);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vvi table(n, vi(n));
        for (auto &r : table)
            for (auto &e : r)
                cin >> e;
        vvi ans(n, vi(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans[i][j] = table[i][j];
                for (int k = 0; k < n; ++k) {
                    ans[i][j] ^= table[i][k];
                    ans[i][j] ^= table[k][j];
                }
            }
        }
        ll cnt = 0;
        for (int i = 0; i < n; ++i)
            cnt += accumulate(all(ans[i]), 0ll);
        cout << cnt << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (ans[i][j])
                    cout << i << ' ' << j << '\n';
            }
        }
    }
}