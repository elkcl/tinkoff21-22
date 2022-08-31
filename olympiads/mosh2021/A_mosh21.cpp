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
using ull = uint64_t;
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
/*#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif*/
#define endl '\n'

/*ii d(int x, int y) {
    return {(x + y) / 2, (x - y + 1) / 2};
}*/

int dist(int x1, int y1, int x2, int y2) {
    int ans = 2;
    if (x1 + y1 == x2 + y2)
        --ans;
    if (x1 - y1 == x2 - y2)
        --ans;
    return ans;
}


signed main() {
    fast_io
    freopen("/home/elk/CLionProjects/tinkoff21-22/assets/mosh2021/a2.txt", "r", stdin);
    freopen("/home/elk/CLionProjects/tinkoff21-22/assets/mosh2021/ans/a2_ans.txt", "w", stdout);

    int t;
    cin >> t;
    while (t--) {
        int n, x1, y1, x2, y2;
        cin >> n >> x1 >> y1 >> x2 >> y2;
        --x1, --x2, --y1, --y2;
        if (x2 % 2 == y2 % 2) {
            cout << "-1" << endl;
            continue;
        }
        if (x1 % 2 != y1 % 2) {
            cout << dist(x1, y1, x2, y2) << endl;
            continue;
        }
        int ans = 2e9;
        for (int i = -2; i < 3; ++i) {
            if (i == 0)
                continue;
            if (x1 + i < 0)
                continue;
            if (x1 + i >= n)
                continue;
            for (int j = -2; j < 3; ++j) {
                if (j == 0)
                    continue;
                if (abs(i) + abs(j) != 3)
                    continue;
                if (y1 + j < 0)
                    continue;
                if (y1 + j >= n)
                    continue;
                ans = min(ans, 1 + dist(x1 + i, y1 + j, x2, y2));
            }
        }
        cout << ans << endl;
    }
}