#ifndef ONPC
#pragma GCC optimize("O2")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,tune=native")
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


struct fenwick {
    vvi f;
    int sz;
    fenwick(int n): sz{n} {
        f.resize(n + 1);
    }

    int sum(int r, int y1, int y2) {
        int res = 0;
        for (int i = r; i > 0; i -= i & -i) {
            auto from = lower_bound(all(f[i]), y1);
            auto to = upper_bound(all(f[i]), y2);
            res += to - from;
        }
        return res;
    }

    int sum(int x1, int y1, int x2, int y2) {
        ++x1, ++x2;
       if (x1 == 1)
           return sum(x2, y1, y2);
        return sum(x2, y1, y2) - sum(x1 - 1, y1, y2);
    }

    void add(int x, int y) {
        ++x;
        for (int i = x; i <= sz; i += i & -i) {
            f[i].push_back(y);
        }
    }
};

struct pt {
    int x, y;
};

bool comp_x(const pt &a, const pt &b) {
    return a.x < b.y;
}

bool comp_y(const pt &a, const pt &b) {
    return a.y < b.y;
}

bool comp_xy(const pt &a, const pt &b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int main() {
    fast_io

    int n;
    cin >> n;
    vector<pt> v(n);
    vi uzx(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x >> v[i].y;
        uzx[i] = v[i].x;
    }
    sort(all(uzx));
    auto last_x = unique(all(uzx));
    uzx.erase(last_x, uzx.end());
    int x = uzx.size();
    map<int, int> zx;
    for (int i = 0; i < x; ++i) {
        zx[uzx[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        v[i].x = zx[v[i].x];
    }
    sort(all(v), comp_y);

    fenwick fw(x);
    for (int i = 0; i < n; ++i) {
        fw.add(v[i].x, v[i].y);
    }

    int m;
    cin >> m;
    for (int q = 0; q < m; ++q) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        auto itl = zx.lower_bound(x1);
        auto itr = zx.lower_bound(x2);
        if (itl == zx.end()) {
            cout << "0\n";
            continue;
        }
        if (itr == zx.end()) {
            --itr;
        }
        if (x2 < itr->first) {
            if (itr == zx.begin()) {
                cout << "0\n";
                continue;
            }
            else {
                --itr;
            }
        }
        cout << fw.sum(itl->second, y1, itr->second, y2) << '\n';
    }
}