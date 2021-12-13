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
using lll = __int128;

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
    for (int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        lll o = 1;
        lll q1 = o * 5 * a * a + 4;
        lll q2 = o * 5 * a * a - 4;
        lll sq1 = static_cast<lll>(floor(sqrt(q1)));
        sq1 = sq1 * sq1;
        lll sq2 = static_cast<lll>(floor(sqrt(q2)));
        sq2 = sq2 * sq2;
        if (q1 == sq1 || q2 == sq2) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}