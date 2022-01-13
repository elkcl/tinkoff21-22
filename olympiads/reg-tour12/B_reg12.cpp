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
    vi a(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        r[a[i]] = i;
    }

    int ans = bin_search(1, n - 1, [n, &a, &r](int x) -> bool {
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            if (a[i] > x)
                continue;
            if (a[i] % 2 == 0) {
                if (a[i] == x)
                    continue;
                int j = r[a[i] + 1];
                if (i < j) {
                    s.push(a[i]);
                } else {
                    if (s.top() == a[i])
                        s.pop();
                    else
                        return false;
                }
            } else {
                int j = r[a[i] - 1];
                if (i < j) {
                    s.push(a[i] - 1);
                } else {
                    if (s.top() == a[i] - 1)
                        s.pop();
                    else
                        return false;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (a[i] > x)
                continue;
            if (a[i] % 2 == 1) {
                if (a[i] == x)
                    continue;
                int j = r[a[i] + 1];
                if (i < j) {
                    s.push(a[i]);
                } else {
                    if (s.top() == a[i])
                        s.pop();
                    else
                        return false;
                }
            } else {
                if (a[i] == 0)
                    continue;
                int j = r[a[i] - 1];
                if (i < j) {
                    s.push(a[i] - 1);
                } else {
                    if (s.top() == a[i] - 1)
                        s.pop();
                    else
                        return false;
                }
            }
        }
        return true;
    });
    cout << ans << '\n';
}