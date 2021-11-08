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

struct fenwick {
    int n;
    vi t;

    fenwick(int _s) {
        n = _s;
        t.resize(_s + 1, 0);
    }

    int get(int k) {
        int res = 0;
        for (int i = k; i > 0; i -= i & -i)
            res += t[i];
        return res;
    }

    void upd(int k, int x) {
        for (int i = k; i <= n; i += i & -i)
            t[i] += x;
    }

    int find_last_less(int x) {
        int k = 0;
        for (int i = static_cast<int>(log2(n)); i >= 0; --i) {
            if (k + (1 << i) <= n && t[k + (1 << i)] < x) {
                k += (1 << i);
                x -= t[k];
            }
        }
        return k;
    }
};

int main() {
    fast_io

    int n;
    cin >> n;
    vi a(n);
    for (int &e : a)
        cin >> e;
    fenwick fw(2e5 + 1);
    for (int i = 1; i <= 2e5 + 1; ++i) {
        fw.upd(i, 1);
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] > 0) {
            int x = fw.find_last_less(fw.get(a[i] - 1) + 1) + 1;
            cout << x << '\n';
            fw.upd(x, -1);
        } else {
            fw.upd(-a[i], 1);
        }
    }
}