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

struct data_t {
    int ans, l, r, n;
    bool neut = false;
};

data_t operator+(const data_t &a, const data_t &b) {
    if (a.neut)
        return b;
    if (b.neut)
        return a;
    if (a.ans == a.n && b.ans == b.n)
        return {a.n + b.n, a.n + b.n, a.n + b.n, a.n + b.n};
    if (a.l == a.n)
        return {max({a.l + b.l, b.ans}), a.l + b.l, b.r, a.n + b.n};
    if (b.r == b.n)
        return {max({a.r + b.r, a.ans}), a.l, a.r + b.r, a.n + b.n};
    return {max({a.ans, b.ans, a.r + b.l}), a.l, b.r, a.n + b.n};
}

struct segtree {
    int n;
    vector<data_t> t;
    vi left, right;

    segtree(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        left.resize(4 * n);
        right.resize(4 * n);

        build(a, 1, 0, n);
    }

    data_t build(const vi &a, int v, int l, int r) {
        left[v] = l;
        right[v] = r;
        if (l + 1 == r) {
            return t[v] = {a[l] == 0, a[l] == 0, a[l] == 0, 1};
        }
        int m = (l + r) / 2;
        return t[v] = build(a, 2 * v, l, m) + build(a, 2 * v + 1, m, r);
    }

    data_t get(int ql, int qr, int v = 1) {
        if (qr <= left[v] || right[v] <= ql)
            return {0, 0, 0, 0, true};
        if (ql <= left[v] && right[v] <= qr)
            return t[v];

        return get(ql, qr, 2 * v) + get(ql, qr, 2 * v + 1);
    }

    void upd(int q, int x, int v = 1) {
        if (q + 1 <= left[v] || right[v] <= q)
            return;
        if (q <= left[v] && right[v] <= q + 1) {
            t[v] = {x == 0, x == 0, x == 0, 1};
            return;
        }

        upd(q, x, 2 * v);
        upd(q, x, 2 * v + 1);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
};

int main() {
    fast_io

    int n, m;
    cin >> n;
    vi h(n);
    for (int &e : h)
        cin >> e;
    segtree seg(h);
    cin >> m;
    for (int q = 0; q < m; ++q) {
        string t;
        cin >> t;
        if (t == "QUERY") {
            int l, r;
            cin >> l >> r;
            cout << seg.get(l - 1, r).ans << '\n';
        } else {
            int i, x;
            cin >> i >> x;
            seg.upd(i - 1, x);
        }
    }
}