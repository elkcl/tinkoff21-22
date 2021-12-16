#ifndef ONPC
#pragma GCC optimize("O3")

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

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

const int INF = 1.7e9;

int main() {
    fast_io

    int n;
    cin >> n;
    vi a(n + 2), lbv(n + 2, -1), rbv(n + 2, -1), lmv(n + 2, -1), rmv(n + 2, -1);
    a[0] = a[n + 1] = INF;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    stack<int> s;
    for (int i = 0; i < n + 2; ++i) {
        while (!s.empty() && a[s.top()] < a[i])
            s.pop();
        if (!s.empty())
            lmv[i] = s.top();
        s.push(i);
    }
    while (!s.empty())
        s.pop();
    for (int i = n + 1; i >= 0; --i) {
        while (!s.empty() && a[s.top()] <= a[i])
            s.pop();
        if (!s.empty())
            rmv[i] = s.top();
        s.push(i);
    }

    int m = static_cast<int>(floor(log2(*max_element(all(a)))) + 1);
    for (ui j = 0; j < m; ++j) {
        int last = -1;
        for (int i = 0; i < n + 2; ++i) {
            if ((a[i] & (1u << j)) == 0) {
                if (last == -1)
                    continue;
                if (lbv[i] == -1 || (i - lbv[i]) > (i - last))
                    lbv[i] = last;
            } else {
                last = i;
            }
        }
        last = -1;
        for (int i = n + 1; i >= 0; --i) {
            if ((a[i] & (1u << j)) == 0) {
                if (last == -1)
                    continue;
                if (rbv[i] == -1 || (rbv[i] - i) > (last - i))
                    rbv[i] = last;
            } else {
                last = i;
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int lb = i - lbv[i];
        int rb = rbv[i] - i;
        int lm = i - lmv[i];
        int rm = rmv[i] - i;

        if (lb < lm && rb < rm)
            ans += lm * rm - lb * rb;
        else if (rb < rm)
            ans += lm * (rm - rb);
        else if (lb < lm)
            ans += (lm - lb) * rm;
    }
    cout << ans << '\n';
}