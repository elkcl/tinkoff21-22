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


int main() {
    fast_io

    int s, e, n;
    cin >> s >> e >> n;
    vi x(n);
    for (int &i: x)
        cin >> i;
    sort(all(x));
    auto p1 = lower_bound(all(x), s);
    if (p1 == x.end() || (p1 != x.begin() && s - *(p1 - 1) < *p1 - s))
        --p1;
    auto p2 = lower_bound(all(x), e);
    if (p2 == x.end() || (p2 != x.begin() && e - *(p2 - 1) < *p2 - e))
        --p2;
    cout << min(abs(s - e), abs(s - *p1) + abs(e - *p2) + 1) << '\n';
}