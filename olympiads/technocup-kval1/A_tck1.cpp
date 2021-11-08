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


int main() {
    fast_io

    int t;
    cin >> t;
    for (int q = 0; q < t; ++q) {
        int n;
        cin >> n;
        vi a(n);
        for (int &e : a)
            cin >> e;
        ll s = accumulate(all(a), 0ll);
        bool prime = true;
        for (int d = 2; d * d <= s; ++d) {
            if (s % d == 0) {
                prime = false;
                break;
            }
        }
        if (!prime) {
            cout << n << '\n';
            for (int i = 1; i <= n; ++i)
                cout << i << ' ';
            cout << '\n';
        } else {
            cout << n - 1 << '\n';
            bool skipped = false;
            for (int i = 1; i <= n; ++i) {
                if (!skipped && a[i - 1] % 2 == 1) {
                    skipped = true;
                } else {
                    cout << i << ' ';
                }
            }
            cout << '\n';
        }
    }
}