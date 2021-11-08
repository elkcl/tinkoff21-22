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

struct segtree {
    int n;
    vi t, left, right;

    segtree(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        left.resize(4 * n);
        right.resize(4 * n);

        build(a, 1, 0, n);
    }

    int build(const vi &a, int v, int l, int r) {
        left[v] = l;
        right[v]= r;
        if (l + 1 == r) {
            return t[v] = a[l];
        }
        int m = (l + r) / 2;
        return t[v] = build(a, 2 * v, l, m) + build(a, 2 * v + 1, m, r);
    }

    int get(int ql, int qr, int v = 1) {
        if (qr <= left[v] || right[v] <= ql)
            return 0;
        if (ql <= left[v] && right[v] <= qr)
            return t[v];
        return get(ql, qr, 2 * v) + get(ql, qr, 2 * v + 1);
    }

    void upd(int q, int x, int v = 1) {
        if (q + 1 <= left[v] || right[v] <= q)
            return;
        if (q <= left[v] && right[v] <= q + 1) {
            t[v] += x;
            return;
        }
        upd(q, x, 2 * v);
        upd(q, x, 2 * v + 1);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    int lower_bound(int k, int v = 1) {
        if (left[v] + 1 == right[v])
            return left[v];
        if (k > t[2 * v])
            return lower_bound(k - t[2 * v], 2 * v + 1);
        return lower_bound(k, 2 * v);
    }
};

int main() {
    fast_io

    int n;
    cin >> n;
    vi a(n);
    for (int &e : a)
        cin >> e;
    vi v(2e5 + 1, 1);
    segtree seg(v);
    for (int i = 0; i < n; ++i) {
        if (a[i] > 0) {
            int x = seg.lower_bound(seg.get(0, a[i]) + 1);
            cout << x << '\n';
            seg.upd(x, -1);
        } else {
            seg.upd(-a[i], 1);
        }
    }
}