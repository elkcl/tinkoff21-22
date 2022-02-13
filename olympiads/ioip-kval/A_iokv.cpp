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

struct el {
    int v;
    int c = 1;
};

bool operator<(const el &a, const el &b) {
    return a.v < b.v;
}

int32_t main() {
    fast_io

    int n;
    cin >> n;
    vector<el> a(n);
    for (auto &e : a) {
        cin >> e.v;
    }
    sort(all(a));
    list<el> l(all(a));
    int last = -1;
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (it->v == last) {
            --it;
            ++(it->c);
            ++it;
            auto next = ++it;
            l.erase(--it);
            it = next;
            if (it == l.end())
                break;
        } else {
            last = it->v;
        }
    }

    int ans = 0;
    while (!l.empty()) {
        int last = l.front().v;
        if (l.front().c == 1) {
            l.erase(l.begin());
        } else {
            --l.front().c;
        }
        auto curr = l.begin();
        while (curr != l.end()) {
            while (curr != l.end() && curr->v < last + 2)
                ++curr;
            if (curr != l.end()) {
                last = curr->v;
                if (curr->c == 1) {
                    auto next = ++curr;
                    l.erase(--curr);
                    curr = next;
                } else {
                    --(curr->c);
                    ++curr;
                }
            }
        }
        ++ans;
    }
    cout << ans << '\n';
}