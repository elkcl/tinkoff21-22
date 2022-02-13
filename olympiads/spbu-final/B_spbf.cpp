#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
//#pragma GCC optimize("unroll-loops")
#endif

// sub 1337

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

bool FLIP = false;

void flip() {
    FLIP = true;
}

bool wait_until(int t) {
    if (FLIP) {
        cout << "Flip and wait" << endl;
        FLIP = false;
    }
    string s;
    cin >> s;
    if (s == "Tired" || s == "Fail")
        return false;
    int k = (s.size() - 3) / 2;
    t -= k;
    while (t > 0) {
        cout << "Wait" << endl;
        cin >> s;
        if (s == "Tired" || s == "Fail")
            return false;
        k = (s.size() - 3) / 2;
        t -= k;
    }
    return true;
}

void stop() {
    cout << "Stop" << endl;
}


int32_t main() {
    fast_io

    int n;
    cin >> n;
    vi k(n);
    for (int i = 0; i < n; ++i)
        cin >> k[i];
    flip();
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < k[i]; ++j) {
            if (wait_until(i + 1)) {
                flip();
            } else {
                return 0;
            }
        }
    }
    stop();
}