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

string ans;

void print(const vi &v) {
//    if (accumulate(all(v), 0ll) % 3 != 0)
//        return;
    string s;
    for (int i : v) {
        s.push_back(static_cast<char>(i + '0'));
    }
    if (s.empty()) {
        s.push_back('0');
    }
    while (s[0] == '0' && s.size() > 1)
        s.erase(s.begin());
    if (s.size() > ans.size() || (s.size() == ans.size() && s > ans)) {
        ans = move(s);
    }
}

int32_t main() {
    fast_io

    int n;
    cin >> n;
    vi v(n);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        v[i] = c - '0';
    }
    ll sum = accumulate(all(v), 0ll);
    int r = (sum % 3);
    if (r == 0) {
        for (int e : v)
            cout << e;
        cout << '\n';
        return 0;
    }
    if (n <= 6 && n > 3) {
        int num = 0;
        for (int i = 0; i < n; ++i) {
            num *= 10;
            num += v[i];
        }
//        if (num != 54784)
//            assert(num < 700223);
    }
    bool found = false;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (v[i] % 3 == r) {
            last = i;
            if (i == n - 1 || v[i] < v[i + 1]) {
                found = true;
                int temp = v[i];
                v.erase(v.begin() + i);
                print(v);
                v.insert(v.begin() + i, temp);
                break;
            }
        }
    }
    if (last != -1) {
        int temp = v[last];
        v.erase(v.begin() + last);
        print(v);
        v.insert(v.begin() + last, temp);
    }

    found = false;
    last = -1;
    for (int i = 0; i < n; ++i) {
        if (v[i] % 3 == 3 - r) {
            last = i;
            if (i == n - 1 || v[i] < v[i + 1]) {
                found = true;
                v.erase(v.begin() + i);
                --n;
                break;
            }
        }
    }
    if (!found && last != -1) {
        v.erase(v.begin() + last);
        --n;
    }
    if (!found && last == -1) {
        cout << ans << '\n';
        return 0;
    }
    found = false;
    last = -1;
    for (int i = 0; i < n; ++i) {
        if (v[i] % 3 == 3 - r) {
            last = i;
            if (i == n - 1 || v[i] < v[i + 1]) {
                found = true;
                v.erase(v.begin() + i);
                --n;
                break;
            }
        }
    }
    if (!found && last != -1) {
        v.erase(v.begin() + last);
        --n;
    }

    print(v);
    cout << ans << '\n';
}