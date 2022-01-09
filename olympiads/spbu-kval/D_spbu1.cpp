#ifdef ONPC
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
//#include <optional>
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
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

const int INF = 1e9;

template<typename F>
int bin_search(int l, int r, const F &f) {
    --l, ++r;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (f(m))
            l = m;
        else
            r = m;
    }
    return r;
}

int main() {
    fast_io

    int n;
    cin >> n;
    vll a(n);
    for (auto &el : a)
        cin >> el;
    sort(all(a));
    vll p(n + 1, 0);
    for (int i = 0; i < n; ++i)
        p[i + 1] = p[i] + a[i];
    int ans = INF;
    for (int i = 2; i < n; ++i) {
        int c = bin_search(0, i - 2, [&p, &a, i](int x) {
            return p[i] - p[x] > a[i];
        });
        if (c == 0)
            continue;
        ans = min(ans, i - c + 2);
    }
    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
}