#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
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

struct pair_hash {
    size_t operator()(const ii &p) const {
        ll l = p.first;
        ll r = p.second;
        hash<ll> h;
        return h((l << 32) + r);
    }
};

unordered_map<ii, ll, pair_hash> cache;

ll check(int l, int r) {
    auto it = cache.find({l, r});
    if (it != cache.end())
        return it->second;
    cout << "? " << l << ' ' << r << endl;
    int x;
    cin >> x;
    assert(x != -1);
    cache[{l, r}] = x;
    return x;
}

ll solve(ll x) {
    ll d = 1 + 8 * x;
    ll sd = static_cast<ll>(sqrt(d));
    if (sd * sd != d)
        return -1;
    if ((1 + sd) % 2 != 0)
        return -1;
    return (1 + sd) / 2;
}

bool check_ans(int n, int i, int j, int k) {

}

void ans(int n, int l, int r, ll curr) {
    int q = (l + r + 1) / 2;
    ll a = check(l, q - 1);
    if (a == curr) {
        ans(n, l, q - 1, curr);
    } else if (a == 0) {
        ans(n, q, r, curr);
    } else {
        ll b = check(q, r);
        ll x = solve(a);
        ll y = solve(b);
        if (a + b == curr) {
            cout << "! " << q - x << ' ' << q << ' ' << q + y - 1 << endl;
            return;
        }
        bool correct = true;
        if (x != -1) {
            ll mn = (curr - a - b) / 2;
            if (mn % x != 0)
                correct = false;
            if (correct) {
                ll m = mn / x;
                ll p = solve(b - m*(m-1)/2);
                correct = check_ans(n, q - x, q + m - 1, p - 1 + q + m - 1);
            }
        }
        if (!correct && y != -1) {
            ll mn = (curr - a - b) / 2;
            if (mn % x != 0)
                correct = false;
        }
    }
}

int main() {
    fast_io


}