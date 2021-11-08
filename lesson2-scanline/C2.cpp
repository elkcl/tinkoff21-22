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

const int INF = 2e9;

vi uzx, uzy;

int dist_x(int zx1, int zx2) {
    return abs(uzx[zx1] - uzx[zx2]);
}

int dist_y(int zy1, int zy2) {
    return abs(uzy[zy1] - uzy[zy2]);
}

struct data_t {
    int min, cnt;
};

data_t operator+(const data_t &a, const data_t &b) {
    if (a.min == b.min)
        return {a.min, a.cnt + b.cnt};
    if (a.min < b.min)
        return a;
    return b;
}

struct segtree {
    int n;
    vector<data_t> t;
    vi left, right, aff;

    segtree(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        left.resize(4 * n);
        right.resize(4 * n);
        aff.resize(4 * n);

        build(a, 1, 0, n);
    }

    data_t build(const vi &a, int v, int l, int r) {
        left[v] = l;
        right[v] = r;
        if (l + 1 == r) {
            return t[v] = {a[l], dist_y(l, r)};
        }
        int m = (l + r) / 2;
        return t[v] = build(a, 2 * v, l, m) + build(a, 2 * v + 1, m, r);
    }

    void push(int v) {
        t[v].min += aff[v];

        aff[2 * v] += aff[v];
        aff[2 * v + 1] += aff[v];

        aff[v] = 0;
    }

    data_t fresh(int v) {
        return {t[v].min + aff[v], t[v].cnt};
    }

    data_t get(int ql, int qr, int v = 1) {
        if (qr <= left[v] || right[v] <= ql)
            return {INF, 0};
        if (ql <= left[v] && right[v] <= qr)
            return fresh(v);

        push(v);
        return get(ql, qr, 2 * v) + get(ql, qr, 2 * v + 1);
    }

    int ans(int ql, int qr) {
        data_t g = get(ql, qr);
        if (g.min != 0)
            return dist_y(ql, qr);
        return dist_y(ql, qr) - g.cnt;
    }

    void add(int ql, int qr, int x, int v = 1) {
        if (qr <= left[v] || right[v] <= ql)
            return;
        if (ql <= left[v] && right[v] <= qr) {
            aff[v] += x;
            return;
        }

        push(v);
        add(ql, qr, x, 2 * v);
        add(ql, qr, x, 2 * v + 1);
        t[v] = fresh(2 * v) + fresh(2 * v + 1);
    }
};

struct rect {
    int x1, y1, x2, y2;
};

enum event_type {
    LEFT,
    RIGHT
};

struct event {
    event_type t;
    int x, y1, y2;

    bool operator<(const event &other) const {
        if (this->x == other.x)
            return this->t < other.t;
        return this->x < other.x;
    }
};

int main() {
    fast_io

    int n;
    cin >> n;
    if (n == 0) {
        cout << "0\n";
        return 0;
    }
    vector<rect> v(n);
    uzx.resize(2 * n);
    uzy.resize(2 * n);
    unordered_map<int, int> zx, zy;
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
        uzx[2 * i] = v[i].x1;
        uzx[2 * i + 1] = v[i].x2;
        uzy[2 * i] = v[i].y1;
        uzy[2 * i + 1] = v[i].y2;
    }

    sort(all(uzx));
    auto last_uzx = unique(all(uzx));
    uzx.erase(last_uzx, uzx.end());
    int xs = uzx.size();
    for (int i = 0; i < xs; ++i)
        zx[uzx[i]] = i;

    sort(all(uzy));
    auto last_uzy = unique(all(uzy));
    uzy.erase(last_uzy, uzy.end());
    int ys = uzy.size();
    for (int i = 0; i < ys; ++i)
        zy[uzy[i]] = i;

    vector<event> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        ev.push_back({LEFT, zx[v[i].x1], zy[v[i].y1], zy[v[i].y2]});
        ev.push_back({RIGHT, zx[v[i].x2], zy[v[i].y1], zy[v[i].y2]});
    }
    int evs = ev.size();

    sort(all(ev));
    vi segv(ys - 1, 0);
    segtree seg(segv);
    ll ans = 0;
    seg.add(ev[0].y1, ev[0].y2, 1);
    for (int i = 1; i < evs; ++i) {
        ans += static_cast<ll>(dist_x(ev[i - 1].x, ev[i].x)) * seg.ans(0, ys - 1);
        if (ev[i].t == LEFT)
            seg.add(ev[i].y1, ev[i].y2, 1);
        else
            seg.add(ev[i].y1, ev[i].y2, -1);
    }

    cout << ans << '\n';
}