#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
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

    int n;
    cin >> n;
    if (n % 2 != 0) {
        cout << n - 3 << '\n';
        for (int i = 3; i < n; ++i)
            cout << "1 " << i << '\n';
    } else {
        vii ans;
        ans.push_back({1, 1 + n / 2});
        for (int i = 2; i < 1 + n / 2; ++i) {
            ans.push_back({i, 2 + n - i});
            if (2 + n / 2 - i > i + 1)
                ans.push_back({i, 2 + n / 2 - i});
        }
        for (int i = 2 + n / 2; i <= n; ++i) {
            if (2 + 3 * n / 2 - i > i + 1)
                ans.push_back({i, 2 + 3 * n / 2 - i});
        }
        if (ans.size() < n - 3) {
            cout << n - 3 << '\n';
            for (int i = 3; i < n; ++i)
                cout << "1 " << i << '\n';
        } else {
            cout << ans.size() << '\n';
            for (auto &an: ans)
                cout << an.first << ' ' << an.second << '\n';
        }
    }
}