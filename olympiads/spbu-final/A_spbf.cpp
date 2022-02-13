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

using namespace std;
using ll = int64_t;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = uint32_t;
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

    int n;
    cin >> n;
    vll a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        while (a[i] != 0 && a[i] % 10 == 0) {
            a[i] /= 10;
            ++b[i];
        }
    }
    ll ans = *min_element(all(b));
    ll sum = 0;
    const ll M = 10000000000;
    for (int i = 0; i < n; ++i) {
        if (b[i] - ans < 10) {
            ll curr = a[i];
            for (int j = 0; j < b[i] - ans; ++j)
                curr *= 10;
            sum += curr;
            sum %= M;
        }
    }
    while (sum != 0 && sum % 10 == 0) {
        sum /= 10;
        ++ans;
    }
    cout << ans << '\n';
}