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

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

int po(int a, int k, int m) {
    a %= m;
    if (k == 0)
        return 1;
    if (k % 2 == 0) {
        ll t = po(a, k / 2, m);
        return (t * t) % m;
    } else {
        return (po(a, k - 1, m) * 1ll * a) % m;
    }
}


int main() {
    fast_io

    int p;
    cin >> p;
    int lastf = 1;
    for (int b = 0; b < p; b += 100) {
        int size;
        if (b + 100 < p) {
            size = 101;
        } else if (p % 100 == 0) {
            size = 100;
        } else if (p % 100 == 1) {
            break;
        } else {
            size = p % 100;
        }
        //int size = b + 100 < p ? 101 : (p % 100 == 0 ? 100 : p % 100);
        vi v(size, 1);
        v[0] = lastf;
        for (int i = 1; i < size; ++i)
            v[i] = ((i + b) * 1ll * v[i - 1]) % p;
        lastf = v[size - 1];
        vi r(size, 1);
        r[size - 1] = po(v[size - 1], p - 2, p);
        for (int i = size - 2; i >= 1; --i)
            r[i] = ((i + b + 1) * 1ll * r[i + 1]) % p;
        vi res(size, 1);
        for (int i = 1; i < size; ++i)
            res[i] = (v[i - 1] * 1ll * r[i]) % p;

        ll ans = 0;
        for (int i = 1; i < size; ++i) {
            ans += res[i];
            ans %= p;
        }
        cout << ans << '\n';
    }
}