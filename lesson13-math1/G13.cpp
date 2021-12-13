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

unordered_map<int, ii> mer(unordered_map<int, ii> a, unordered_map<int, ii> b, int s) {
    for (auto& [p, v] : a) {
        auto& [k, cnt] = v;
        if (b.find(p) == b.end()) {
            if (k == 0)
                ++cnt;
            else
                v = {0, 1};

        }
    }
    for (auto&& [p, v] : b) {
        auto&& [k, cnt] = v;
        if (a.find(p) != a.end()) {
            if (a[p].first == k)
                a[p].second += cnt;
            else if (a[p].first > k)
                a[p] = v;
        } else {
            a[p] = {0, s};
        }
    }
    return a;
}

int main() {
    fast_io

    int n;
    cin >> n;
    vi a(n);
    for (int &i : a)
        cin >> i;

    int ma = *max_element(all(a));
    vi sieve(ma+1, 0);
    for (int i = 2; i * 1ll * i <= ma; ++i) {
        if (sieve[i] == 0) {
            sieve[i] = i;
            for (int j = i * i; j <= ma; j += i) {
                if (sieve[j] == 0)
                    sieve[j] = i;
            }
        }
    }
    for (int i = 2; i <= ma; ++i) {
        if (sieve[i] == 0) {
            sieve[i] = i;
        }
    }

    vector<unordered_map<int, ii>> facs(n);
    for (int i = 0; i < n; ++i) {
        while (a[i] > 1) {
            if (facs[i].find(sieve[a[i]]) == facs[i].end())
                facs[i][sieve[a[i]]] = {1, 1};
            else
                ++facs[i][sieve[a[i]]].first;
            a[i] /= sieve[a[i]];
        }
    }

    unordered_map<int, ii> curr = move(facs[0]);
    for (int i = 1; i < n; ++i)
        curr = mer(move(curr), move(facs[i]), i);
    int ans = 1e9;
    for (auto&& [p, v] : curr)
        ans = min(ans, v.second);
    if (ans == 1e9 || ans == n)
        ans = -1;
    cout << ans << '\n';
}