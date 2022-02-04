
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

#define int int64_t

int32_t main() {
    fast_io
    freopen("../assets/mosh_a2.txt", "r", stdin);
    freopen("../assets/test_ans/mosh_a2_ans2.txt", "w", stdout);

    const int zsum = 30;
    const int nsum = 28;
    const vi zp{0, 4, 9, 11, 14, 17, 18, 23, 27, 28};
    const vi np{0, 2, 7, 9, 12, 15, 16, 21, 25, 26};

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        if (k == 0) {
            cout << "0\n";
            continue;
        }
        ll ans = 0;
        ans += 1ll * (k / 10) * zsum;
        ans += zp[k % 10];
        k /= 10;
        while (k != 0) {
            if (k / 10 == 0) {
                ans += np[k % 10];
            } else {
                ans += nsum;
                ans += 1ll * (k / 10 - 1) * zsum;
                ans += zp[k % 10];
            }
            k /= 10;
        }
        cout << ans << '\n';
    }
}