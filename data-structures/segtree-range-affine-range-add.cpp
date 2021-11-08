/*#ifndef ONPC
#pragma GCC optimize("O2")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,tune=native")
//#pragma GCC optimize("unroll-loops")
#endif*/

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

const int M = 998'244'353;

struct affine {
    ll k, b;
};


struct segtree {
    int n;
    vll t;
    vector<affine> aff;

    segtree(const vi &a) {
        n = a.size();
        t.resize(n * 4, 0);
        aff.resize(n * 4, {1, 0});
        build(a, 1, 0, n);
    }

    ll build(const vi &a, int v, int l, int r) {
        if (l + 1 == r) {
            return t[v] = a[l];
        }
        int m = (l + r) / 2;
        return t[v] = (build(a, 2 * v, l, m) + build(a, 2 * v + 1, m, r)) % M;
    }

    void push(int v, int l, int r) {
        t[v] *= aff[v].k;
        t[v] += aff[v].b * (r - l);
        t[v] %= M;

        aff[2 * v].k *= aff[v].k;
        aff[2 * v].b *= aff[v].k;
        aff[2 * v].b += aff[v].b;
        aff[2 * v].k %= M;
        aff[2 * v].b %= M;

        aff[2 * v + 1].k *= aff[v].k;
        aff[2 * v + 1].b *= aff[v].k;
        aff[2 * v + 1].b += aff[v].b;
        aff[2 * v + 1].k %= M;
        aff[2 * v + 1].b %= M;

        aff[v].k = 1;
        aff[v].b = 0;
    }

    ll fresh(int v, int l, int r) const {
        return (t[v] * aff[v].k + aff[v].b * (r - l)) % M;
    }

    ll get(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return 0;
        if (ql <= l && r <= qr)
            return fresh(v, l, r);

        push(v, l, r);
        int m = (l + r) / 2;
        return (get(ql, qr, 2 * v, l, m) + get(ql, qr, 2 * v + 1, m, r)) % M;
    }

    void upd(int ql, int qr, int k, int b, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return;
        if (ql <= l && r <= qr) {
            aff[v].k *= k;
            aff[v].b *= k;
            aff[v].b += b;
            aff[v].k %= M;
            aff[v].b %= M;
            return;
        }

        push(v, l, r);
        int m = (l + r) / 2;
        upd(ql, qr, k, b, 2 * v, l, m);
        upd(ql, qr, k, b, 2 * v + 1, m, r);
        t[v] = (fresh(2 * v, l, m) + fresh(2 * v + 1, m, r)) % M;
    }
};

int main() {
    fast_io

    int n, Q;
    cin >> n >> Q;
    vi a(n);
    for (int &e : a)
        cin >> e;
    segtree seg(a);
    for (int q = 0; q < Q; ++q) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            seg.upd(l, r, b, c);
        } else if (t == 1) {
            int l, r;
            cin >> l >> r;
            cout << seg.get(l, r) << '\n';
        }
    }
}