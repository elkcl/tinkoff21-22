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

struct pt {
    int x, y;
};

enum event_type {
    QUERY_L,
    POINT,
    QUERY_R
};

struct event {
    event_type t;
    int x, y1, y2 = -1, id = -1;

    bool operator<(const event &other) const {
        if (this->x == other.x) {
            return this->t < other.t;
        }
        return this->x < other.x;
    }
};

struct fenwick {
    int n;
    vi t;

    fenwick(int _s): n{_s} {
        t.resize(n + 1, 0);
    }

    int get(int k) {
        int res = 0;
        for (int i = k; i > 0; i -= i & -i) {
            res += t[i];
        }
        return res;
    }

    int get(int y1, int y2) {
        return get(y2) - get(y1);
    }

    void add(int k, int a) {
        ++k;
        for (int i = k; i <= n; i += i & -i) {
            t[i] += a;
        }
    }
};

int main() {
    fast_io

    int n, m;
    cin >> n;
    vector<pt> pts(n);
    vi uzy(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        uzy[i] = pts[i].y;
    }

    sort(all(uzy));
    auto last_uzy = unique(all(uzy));
    uzy.erase(last_uzy, uzy.end());
    int k = uzy.size();
    map<int, int> zy;
    for (int i = 0; i < k; ++i) {
        zy[uzy[i]] = i;
    }

    cin >> m;
    vector<event> ev;
    ev.reserve(n + 2 * m);
    for (int i = 0; i < n; ++i) {
        ev.push_back({POINT, pts[i].x, zy[pts[i].y]});
    }
    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        auto izy1 = zy.lower_bound(y1);
        if (izy1 == zy.end())
            continue;
        int zy1 = izy1->second;
        auto izy2 = zy.upper_bound(y2);
        int zy2;
        if (izy2 == zy.end())
            zy2 = k;
        else
            zy2 = izy2->second;
        ev.push_back({QUERY_L, x1, zy1, zy2, i});
        ev.push_back({QUERY_R, x2, zy1, zy2, i});
    }
    int evs = ev.size();

    sort(all(ev));
    fenwick fw(k);
    vi ans(m, 0);
    for (int i = 0; i < evs; ++i) {
        switch (ev[i].t) {
            case POINT:
                fw.add(ev[i].y1, 1);
                break;
            case QUERY_L:
                ans[ev[i].id] -= fw.get(ev[i].y1, ev[i].y2);
                break;
            case QUERY_R:
                ans[ev[i].id] += fw.get(ev[i].y1, ev[i].y2);
                break;
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << ans[i] << '\n';
    }
}