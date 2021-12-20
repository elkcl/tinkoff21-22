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

const int INF = 1.9e9;

struct merge_sort_tree {
    vvi t;
    int n;

    merge_sort_tree(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        build(1, 0, n, a);
    }

    void build(int v, int l, int r, const vi &a) {
        if (l + 1 == r) {
            t[v].push_back(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m, r, a);
        t[v].resize(t[2 * v].size() + t[2 * v + 1].size());
        merge(all(t[2 * v]), all(t[2 * v + 1]), t[v].begin());
    }

    int get(int ql, int qr, int x = -1, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (x == -1)
            x = qr - 1;
        if (r <= ql || qr <= l)
            return 0;
        if (ql <= l && r <= qr)
            return t[v].end() - upper_bound(all(t[v]), x);
        int m = (l + r) / 2;
        return get(ql, qr, x, 2 * v, l, m) + get(ql, qr, x, 2 * v + 1, m, r);
    }
};

int main() {
    fast_io

    int n, m;
    cin >> n >> m;
    vi a(m);
    deque<int> b(n);
    for (int &el : a)
        cin >> el, --el;
    for (int &el : b)
        cin >> el, --el;
    vi k;
    //k.reserve(m + n);
    vc used(n, false);
    for (int x : a) {
        if (!used[x]) {
            while (true) {
                int y = b.front();
                k.push_back(y);
                used[y] = true;
                b.pop_front();
                if (x == y)
                    break;
            }
        } else {
            k.push_back(x);
        }
    }
    int t = k.size();

    vi inds(n, INF);
    vi next(t);
    for (int i = t - 1; i >= 0; --i) {
        next[i] = inds[k[i]];
        inds[k[i]] = i;
    }
    merge_sort_tree seg(next);
    vi ans(t);
    for (int i = 0; i < t; ++i) {
        if (next[i] != INF)
            ans[i] = seg.get(i, next[i] + 1);
        else
            ans[i] = n;
    }

    cout << t << '\n';
    for (int el : ans)
        cout << el << ' ';
    cout << '\n';
}