#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
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
using ui = uint32_t;
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif


int32_t main() {
    fast_io

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        if (s.size() == 2) {
            if (s == "00")
                cout << "??\n";
            else if (s == "??")
                cout << "00\n";
            else if (s == "01")
                cout << "0?\n";
            else if (s == "0?")
                cout << "01\n";
            else if (s == "10")
                cout << "?0\n";
            else if (s == "?0")
                cout << "10\n";
            else if (s == "11")
                cout << "1?\n";
            else if (s == "1?")
                cout << "11\n";
            continue;
        }

        int n = s.size();
        int q = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '?') {
                ++q;
            }
        }
        if (q == 0) {
            int z = 0;
            for (int i = 0; i < n; ++i) {
                if (s[i] == '0')
                    ++z;
            }
            if (z == n || z == 0) {
                for (int i = 1; i < n; ++i)
                    s[i] = '?';
            } else if ((s[0] == '0' && z == 1) || (s[0] == '1' && z == n - 1)) {
                s.replace(s.begin() + 1, s.end() - 1, n - 2, '?');
            } else if (z >= n - z) {
                for (int i = 0; i < n; ++i) {
                    if (s[i] == '0')
                        s[i] = '?';
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    if (s[i] == '1')
                        s[i] = '?';
                }
            }
        } else {
            if (s[0] == '0' && s[n - 1] == '1') {
                s.replace(s.begin() + 1, s.end() - 1, n - 2, '1');
                cout << s << '\n';
                continue;
            }
            if (s[0] == '1' && s[n - 1] == '0') {
                s.replace(s.begin() + 1, s.end() - 1, n - 2, '0');
                cout << s << '\n';
                continue;
            }
            if (s[0] == '0' && q == n - 1) {
                s.replace(s.begin() + 1, s.end(), n - 1, '0');
                cout << s << '\n';
                continue;
            }
            if (s[0] == '1' && q == n - 1) {
                s.replace(s.begin() + 1, s.end(), n - 1, '1');
                cout << s << '\n';
                continue;
            }
            bool z = true;
            for (int i = 0; i < n; ++i) {
                if (s[i] == '0') {
                    z = false;
                    break;
                }
            }
            if (z) {
                for (int i = 0; i < n; ++i) {
                    if (s[i] == '?')
                        s[i] = '0';
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    if (s[i] == '?')
                        s[i] = '1';
                }
            }
        }
        cout << s << '\n';
    }
}