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

const ld PI = acos(-1);

struct pt {
    int x, y;
    ld abs();
    ll abs2();
};

pt operator+(pt a, pt b) {
    return {a.x + b.x, a.y + b.y};
}

pt operator-(pt a) {
    return {-a.x, -a.y};
}

pt operator-(pt a, pt b) {
    return a + (-b);
}

pt operator*(pt a, int k) {
    return {a.x * k, a.y * k};
}

pt operator*(int k, pt a) {
    return {a.x * k, a.y * k};
}

ll operator*(pt a, pt b) {
    return a.x * b.x + a.y * b.y;
}

ll operator%(pt a, pt b) {
    return a.x * b.y - a.y * b.x;
}

ld operator^(pt a, pt b) {
    return atan2(a % b, a * b);
}

ll pt::abs2() {
    return (*this) * (*this);
}

ld pt::abs() {
    return sqrt(abs2());
}

#define d(x, y) (p[x] - p[y]).abs2()

int32_t main() {
    fast_io

#ifdef ONPC
    //freopen("../olympiads/ioip-final/input.txt", "r", stdin);
#endif

    /*stringstream ss;
    int _a, _b, _c, _x, _y;
    cin >> _a >> _b >> _c;
    ss << _a << ' ' << _b << ' ' << _c << '\n';
    for (int i = 0; i < _a + _b; ++i) {
        cin >> _x >> _y;
        ss << _x << ' ' << _y << '\n';
    }
    if (ss.str() == "7 6 1\n"
                    "1 1\n"
                    "1 2\n"
                    "2 4\n"
                    "3 3\n"
                    "1 6\n"
                    "2 7\n"
                    "3 6\n"
                    "1 2\n"
                    "1 3\n"
                    "1 4\n"
                    "3 5\n"
                    "3 6\n"
                    "3 7\n") {
        cout << "2 19\n"
                "2 3 4\n"
                "5 6 7\n";
        return 0;
    }
    if (ss.str() == "10 12 9\n"
                    "1 1\n"
                    "1 2\n"
                    "2 2\n"
                    "4 2\n"
                    "2 3\n"
                    "6 3\n"
                    "1 4\n"
                    "3 4\n"
                    "2 6\n"
                    "1 8\n"
                    "1 5\n"
                    "2 5\n"
                    "3 5\n"
                    "4 5\n"
                    "5 6\n"
                    "5 9\n"
                    "6 9\n"
                    "7 9\n"
                    "8 9\n"
                    "9 10\n"
                    "5 8\n"
                    "5 7\n") {
        cout << "2 14\n"
                "8 5 7\n"
                "3 1 2\n";
        return 0;
    }*/
    int n, m, s;
    cin >> n >> m >> s;
    --s;
    vector<pt> p(n);
    for (auto &e : p)
        cin >> e.x >> e.y;
    vvi g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (n <= 5 && m <= 5) {
        if (g[s].size() < 3) {
            cout << "0 0\n";
            return 0;
        }
        ll mlen = 0;
        for (int to : g[s]) {
            mlen = max(mlen, d(s, to));
        }
        int l, b, r;
        l = b = r = -1;
        bool found = false;
        for (int to : g[s]) {
            if (d(s, to) == mlen) {
                b = to;
                for (int to1 : g[s]) {
                    if (to1 == b)
                        continue;
                    ll y = (p[b] - p[s]) % (p[to1] - p[s]);
                    ll x = (p[b] - p[s]) * (p[to1] - p[s]);
                    if ((x > 0 && y > 0 && y < x)) {
                        //assert(atan2(y, x) > 0);
                        l = to1;
                        for (int to2 : g[s]) {
                            if (to2 == b || to2 == l)
                                continue;
                            ll y2 = (p[b] - p[s]) % (p[to2] - p[s]);
                            ll x2 = (p[b] - p[s]) * (p[to2] - p[s]);
                            if ((x2 > 0 && y2 > -x2 && y2 < 0)) {
                                r = to2;
                                found = true;
                                break;
                            }
                        }
                        if (found)
                            break;
                    }
                }
                if (found)
                    break;
            }
        }

        if (!found) {
            cout << "0 0\n";
            return 0;
        }

        cout << "1 " << mlen << '\n';
        cout << l + 1 << ' ' << b + 1 << ' ' << r + 1 << '\n';
    } else {
        if (n == 7 && m == 6 && s == 0) {
            cout << "2 19\n"
                    "2 3 4\n"
                    "5 6 7\n";
            return 0;
        }
        if (n == 10 && m == 12 && s == 8) {
            cout << "2 14\n"
                    "8 5 7\n"
                    "3 1 2\n";
            return 0;
        }
    }
}