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
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct num {
    ll a, b;
};

bool operator<(const num &a, const num &b) {
    if (a.b == b.b)
        return a.a < b.a;
    return a.b < b.b;
}

int32_t main() {
    fast_io

    int n;
    cin >> n;
    vector<num> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].a >> p[i].b;
        while (p[i].a != 0 && p[i].a % 10 == 0) {
            p[i].a /= 10;
            ++p[i].b;
        }
    }
    sort(all(p));
    ll ans = p[0].b;
    ll sum = p[0].a;
    for (int i = 1; i < n; ++i) {
        if (p[i - 1].b != p[i].b) {
            ll tms = p[i].b - p[i - 1].b;
            while (tms > 0 && sum != 0 && sum % 10 == 0) {
                sum /= 10;
                ++ans;
                --tms;
            }
            if (tms != 0)
                break;
            /*ll curr = 1;
            for (ll j = 0; j < p[i].b - p[i - 1].b; ++j)
                curr *= 10;
            if (sum % curr != 0) {
                break;
            }
            sum /= curr;
            ans += p[i].b - p[i - 1].b;*/
        }
        sum += p[i].a;
    }
    while (sum != 0 && sum % 10 == 0) {
        sum /= 10;
        ++ans;
    }
    cout << ans << '\n';
}