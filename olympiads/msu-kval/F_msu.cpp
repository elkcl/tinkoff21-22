#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2")
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
using vvc = vector<vc>;
using ui = uint32_t;
using ull = uint64_t;
using ld = long double;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define endl '\n'

struct segtree {
    int n;
    vi t;
    vi p;

    segtree(int _n) {
        n = _n;
        t.resize(4 * n, 0);
        p.resize(4 * n, 0);
    }

    int fresh(int v) {
        return t[v] + p[v];
    }

    void push(int v) {
        t[v] += p[v];
        p[2 * v] += p[v];
        p[2 * v + 1] += p[v];
        p[v] = 0;
    }

    int get(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return -1;
        if (ql <= l && r <= qr)
            return fresh(v);

        push(v);
        int m = (l + r) / 2;
        return max(get(ql, qr, 2 * v, l, m), get(ql, qr, 2 * v + 1, m, r));
    }

    void add(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (qr <= l || r <= ql)
            return;
        if (ql <= l && r <= qr) {
            ++p[v];
            return;
        }

        push(v);
        int m = (l + r) / 2;
        add(ql, qr, 2 * v, l, m);
        add(ql, qr, 2 * v + 1, m, r);
        t[v] = max(fresh(2 * v), fresh(2 * v + 1));
    }
};

signed main() {
    fast_io

    int n, k, m;
    cin >> n >> k >> m;
    segtree s(n);
    while (m--) {
        int x, y;
        cin >> x >> y;
        if (s.get(x, y) == k) {
            cout << 0 << endl;
        } else {
            s.add(x, y);
            cout << 1 << endl;
        }
    }
}