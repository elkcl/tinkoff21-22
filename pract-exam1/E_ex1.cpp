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
#include <stack>
#include <unordered_set>

#define int int64_t

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
//using ui = unsigned int;
using ld = long double;
using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct segtree_sum {
    int n;
    vi t;
    vi aff;

    explicit segtree_sum(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        aff.resize(4 * n, 0);
        build(1, 0, n, a);
    }

    int build(int v, int l, int r, const vi &a) {
        if (l + 1 == r)
            return t[v] = a[l];
        int m = (l + r) / 2;
        return t[v] = build(2 * v, l, m, a) + build(2 * v + 1, m, r, a);
    }

    int fresh(int v, int l, int r) {
        return t[v] + (r - l) * aff[v];
    }

    void push(int v, int l, int r) {
        t[v] += (r - l) * aff[v];
        aff[2 * v] += aff[v];
        aff[2 * v + 1] += aff[v];
        aff[v] = 0;
    }

    int get(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return 0;
        if (ql <= l && r <= qr)
            return fresh(v, l, r);

        push(v, l, r);
        int m = (l + r) / 2;
        return get(ql, qr, 2 * v, l, m) + get(ql, qr, 2 * v + 1, m, r);
    }

    int get(int q) {
        return get(0, q + 1);
    }

    void upd(int ql, int qr, int x, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return;
        if (ql <= l && r <= qr) {
            aff[v] += x;
            return;
        }

        push(v, l, r);
        int m = (l + r) / 2;
        upd(ql, qr, x, 2 * v, l, m);
        upd(ql, qr, x, 2 * v + 1, m, r);
        t[v] = fresh(2 * v, l, m) + fresh(2 * v + 1, m, r);
    }
};

struct segtree_gcd {
    int n;
    vi t;

    explicit segtree_gcd(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        build(1, 0, n, a);
    }

    int build(int v, int l, int r, const vi &a) {
        if (l + 1 == r)
            return t[v] = a[l];
        int m = (l + r) / 2;
        return t[v] = gcd(build(2 * v, l, m, a), build(2 * v + 1, m, r, a));
    }

    int get(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return 0;
        if (ql <= l && r <= qr)
            return t[v];

        int m = (l + r) / 2;
        return gcd(get(ql, qr, 2 * v, l, m), get(ql, qr, 2 * v + 1, m, r));
    }

    void upd(int ql, int x, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (l + 1 == r) {
            t[v] += x;
            return;
        }

        int m = (l + r) / 2;
        if (ql < m)
            upd(ql, x, 2 * v, l, m);
        else
            upd(ql, x, 2 * v + 1, m, r);
        t[v] = gcd(t[2 * v], t[2 * v + 1]);
    }
};

int32_t main() {
    fast_io

    int n, q;
    cin >> n >> q;
    vi a(n);
    for (int &e : a)
        cin >> e;

    vi a1(n);
    a1[0] = a[0];
    for (int i = 1; i < n; ++i)
        a1[i] = a[i] - a[i - 1];
    vi a2(n);
    a2[0] = a1[0];
    for (int i = 1; i < n; ++i)
        a2[i] = a1[i] - a1[i - 1];
    segtree_sum seg1(a1);
    segtree_gcd seg2(a2);

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            cin >> l >> r;
            --l;
            if (r - l == 1) {
                cout << seg1.get(l) << '\n';
            } else if (r - l == 2) {
                cout << gcd(seg1.get(l), seg1.get(l + 1)) << '\n';
            } else {
                int g1 = seg1.get(l);
                int g2 = seg1.get(l + 1);
                cout << gcd(gcd(g1, g2 - 2 * g1), seg2.get(l + 2, r)) << '\n';
            }
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            seg1.upd(l, r, k);
            if (r < n)
                seg1.upd(r, r + 1, (l - r) * k);
            seg2.upd(l, k);
            if (r < n)
                seg2.upd(r, -(r - l + 1) * k);
            if (r + 1 < n)
                seg2.upd(r + 1, (r - l) * k);
        }
    }
}