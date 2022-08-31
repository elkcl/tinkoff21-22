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

void f(int n, int k, vi &s) {
    if (k == 0) {
        for (auto e : s)
            cout << e << ' ';
        cout << endl;
        return;
    }
    for (int i = k; i <= n; ++i) {
        s.push_back(i);
        f(i - 1, k - 1, s);
        s.pop_back();
    }
}

signed main() {
    fast_io

    int n, k;
    cin >> n >> k;
    vi s;
    f(n, k, s);
}