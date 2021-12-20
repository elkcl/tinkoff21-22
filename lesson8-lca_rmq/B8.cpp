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

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;
using ld = long double;
using i128 = __int128;

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

struct query {
    int x1, y1, x2, y2;
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

vi solve(int n, int m, vector<pt> &pts, vector<query> &qs) {
    vi uzy(n);
    for (int i = 0; i < n; ++i) {
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

    vector<event> ev;
    ev.reserve(n + 2 * m);
    for (int i = 0; i < n; ++i) {
        ev.push_back({POINT, pts[i].x, zy[pts[i].y]});
    }
    for (int i = 0; i < m; ++i) {
        auto [x1, y1, x2, y2] = qs[i];
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

    return ans;
}

void dfs(vvi &g, vi &tin, vi &tout, int &t, int v) {
    tin[v] = t++;
    for (int to : g[v])
        dfs(g, tin, tout, t, to);
    tout[v] = t++;
}

int main() {
    fast_io

    int n;
    cin >> n;
    vvi g1(n), g2(n);
    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        if (s == 0)
            s1 = i;
        else
            g1[s - 1].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        if (s == 0)
            s2 = i;
        else
            g2[s - 1].push_back(i);
    }

    vi tin1(n), tout1(n), tin2(n), tout2(n);
    int t = 0;
    dfs(g1, tin1, tout1, t, s1);
    t = 0;
    dfs(g2, tin2, tout2, t, s2);

    vector<pt> ppl(n);
    for (int v = 0; v < n; ++v)
        ppl[v] = {tin1[v], tin2[v]};
    vector<query> qs(n);
    for (int v = 0; v < n; ++v)
        qs[v] = {tin1[v], tin2[v], tout1[v], tout2[v]};
    vi ans = solve(n, n, ppl, qs);
    ll cnt = accumulate(all(ans), 0ll) - n;
    cout << cnt << '\n';
}