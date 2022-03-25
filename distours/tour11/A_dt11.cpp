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
#include <list>
#include <sstream>

//#define int int64_t

using namespace std;
using ll = int64_t;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = uint32_t;
using ull = uint64_t;
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

vi zf(const vi &s) {
    int n = static_cast<int>(s.size());
    vi z(s.size());
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i > r) {
            z[i] = 0;
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        } else {
            if (z[i - l] + i - 1 >= r) {
                z[i] = r - i + 1;
                while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                    ++z[i];
                if (i + z[i] - 1 > r) {
                    l = i;
                    r = i + z[i] - 1;
                }
            } else {
                z[i] = z[i - l];
            }
        }
    }
    return z;
}

int32_t main() {
    fast_io

    int n;
    cin >> n;
    vi s0(n), s1(n);
    for (auto &e : s0)
        cin >> e;
    for (auto &e : s1)
        cin >> e;

    int off = n + 1;
    vi c1(s1), c2(s0);
    c1.reserve(2 * n + 2);
    c2.reserve(2 * n + 2);
    c1.push_back(-1);
    c2.push_back(-1);
    c1.insert(c1.end(), all(s0));
    c2.insert(c2.end(), all(s1));
    reverse(all(s1));
    vi c3(s1);
    c3.reserve(2 * n + 2);
    c3.push_back(-1);
    c3.insert(c3.end(), all(s0));

    auto z1 = zf(c1);
    auto z2 = zf(c2);
    auto z3 = zf(c3);

    vi ans;
    for (int k = 1; k <= n; ++k) {
        if (z1[off + k - 1] < n - k + 1)
            continue;
        if (k == 1) {
            ans.push_back(k);
            continue;
        }
        if ((n - k + 1) % 2 == 0) {
            if (z2[off + n - k + 1] < k - 1)
                continue;
            ans.push_back(k);
        } else {
            if (z3[off] < k - 1)
                continue;
            ans.push_back(k);
        }
    }

    cout << ans.size() << '\n';
    for (auto &e : ans)
        cout << e << ' ';
    cout << '\n';
}