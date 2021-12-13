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

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

/*ll cnt(ll l, ll r, ll k) {
    if (l % k != 0)
         l += k - (l % k);
    r -= r % k;
    return (r - l) / k + 1;
}*/

int main() {
    fast_io

    ll n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    vc sieve(n + 1, true);
    for (int k = 2; k <= n; ++k) {
        ll l = n * n;
        if (l % k != 0)
            l += k - (l % k);
        l -= n * n;
        for (; l < n + 1; l += k)
            sieve[l] = false;
    }
    ll ans = 0;
    for (int i = 0; i < n + 1; ++i) {
        if (sieve[i])
            ++ans;
    }
    cout << ans << '\n';
}