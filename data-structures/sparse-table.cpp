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

const int INF = 1.5e9;

int main() {
    fast_io

    int n, q;
    cin >> n >> q;
    vi a(n);
    for (int &el : a)
        cin >> el;

    vi logs(n + 1, 0);
    int last_pow = 1;
    for (int i = 2; i <= n; ++i) {
        logs[i] = logs[i - 1];
        if (i >= last_pow * 2) {
            last_pow *= 2;
            ++logs[i];
        }
    }

    vvi sp(n, vi(logs[n] + 1, INF));
    for (int i = 0; i < n; ++i)
        sp[i][0] = a[i];
    for (int l = 1; l < logs[n] + 1; ++l) {
        for (int i = 0; i < n; ++i) {
            if (i + (1 << (l - 1)) >= n)
                break;
            sp[i][l] = min(sp[i][l - 1], sp[i + (1 << (l - 1))][l - 1]);
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = logs[r - l];
        cout << min(sp[l][len], sp[r - (1 << len)][len]) << '\n';
    }
}