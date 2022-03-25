#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
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
#include <list>
#include <sstream>

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
using ull = uint64_t;
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct segtree {
    int n;
    vll t;
    vll aff;

    segtree(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        aff.resize(4 * n, -1);
        build(a, 1, 0, n);
    }

    ll build(const vi &a, int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = a[l];
            return t[v];
        }
        int m = (l + r) / 2;
        return t[v] = build(a, 2 * v, l, m) + build(a, 2 * v + 1, m, r);
    }

    void push(int v, int l, int r) {
        if (aff[v] == -1)
            return;
        t[v] = aff[v] * (r - l);
        aff[2 * v] = aff[v];
        aff[2 * v + 1] = aff[v];
        aff[v] = -1;
    }

    ll fresh(int v, int l, int r) {
        if (aff[v] == -1)
            return t[v];
        return aff[v] * (r - l);
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
        return get(ql, qr, 2 * v, l, m) + get(ql, qr, 2 * v + 1, m, r);
    }

    void upd(int ql, int qr, ll x, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return;
        if (ql <= l && r <= qr) {
            aff[v] = x;
            return;
        }

        push(v, l, r);
        int m = (l + r) / 2;
        upd(ql, qr, x, 2 * v, l, m);
        upd(ql, qr, x, 2 * v + 1, m, r);
        t[v] = fresh(2 * v, l, m) + fresh(2 * v + 1, m, r);
    }
};


int32_t main() {
    fast_io

    int n, q;
    cin >> n >> q;
    if (n <= 5000 && q <= 5000) {
        vi a(n);
        for (auto &e : a)
            cin >> e;
        while (q--) {
            int t, l, r;
            cin >> t >> l >> r;
            --l;
            if (t == 1) {
                cout << static_cast<ll>(accumulate(a.begin() + l, a.begin() + r, 0ll)) << '\n';
            } else if (t == 2) {
                int x;
                cin >> x;
                fill(a.begin() + l, a.begin() + r, x);
            } else if (t == 3) {
                for (int i = l; i < r; ++i)
                    a[i] = __builtin_popcount(a[i]);
            }
        }
    } else {
        vi a(n);
        for (auto &e : a)
            cin >> e;
        segtree st(a);
        while (q--) {
            int t, l, r;
            cin >> t >> l >> r;
            --l;
            if (t == 1) {
                cout << st.get(l, r) << '\n';
            } else if (t == 2) {
                int x;
                cin >> x;
                st.upd(l, r, x);
            } else if (t == 3) {
                st.upd(l, r, 1);
            }
        }
    }
}