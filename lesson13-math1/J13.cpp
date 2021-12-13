#ifndef ONPC
#pragma GCC optimize("O3")

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

tuple<ll, ll, ll> extgcd(ll a, ll b) {
    if (b == 0)
        return {1, 0, a};
    auto [x, y, d] = extgcd(b, a % b);
    return {y, x - (a / b) * y, d};
}

template <typename F>
ll binsearch(ll l, ll r, F check) {
    --l, --r;
    while (r - l > 1) {
        ll m = (l + r) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }
    return r;
}

int main() {
    fast_io

    int t;
    cin >> t;
    while (t--) {
        ll a, b, n, m;
        cin >> a >> b >> n >> m;
        ll c = b - a;
        auto [x0, y0, d] = extgcd(n, m);
        if (c % d != 0) {
            cout << "NO\n";
            continue;
        }
        ll x = (x0 * (c / d)) * n + a;
        ll q = abs(n * (m / d));
        ll k = binsearch(-1e9, 1e9, [x, q](ll v) {
            return x + v * q < 0;
        });
        x += k * q;
        cout << "YES " << x << ' ' << q << '\n';
    }

    /*ll a, b, c;
    cin >> a >> b >> c;
    auto [x0, y0, d] = extgcd(a, b);
    if (c % d != 0) {
        cout << "Impossible\n";
        return 0;
    }
    ll x = x0 * (c / d);
    ll y = y0 * (c / d);
#ifdef ONPC
    cout << "DEBUG: " << x << ' ' << y << '\n';
#endif
    *//*while (x - b / d >= 0) {
        x -= b / d;
        y += a / d;
    }
    while (x < 0) {
        x += b / d;
        y -= a / d;
    }*//*
    ll k = binsearch(-1e9, 1e9, [x, b, d = d](ll v) {
        return x + v * (b / d) < 0;
    });
    cout << x + k * (b / d) << ' ' << y - k * (a / d) << '\n';*/
}