#ifdef ONPC
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
//#include <optional>
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
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

bool check(vector<ui> mat) {
    int n = mat.size();
    for (int i = 0; i < n; ++i) {
        if (mat[i] == 0)
            return false;
        ui c = ~(1u << __builtin_ctz(mat[i]));
        for (int j = i + 1; j < n; ++j)
            mat[j] &= c;
    }
    return true;
}

bool inc(vector<ui> &mat) {
    ui n = mat.size();
    for (auto &row : mat) {
        if (row == (1u << n) - 1) {
            row = 0;
        } else {
            ++row;
            return true;
        }
    }
    return false;
}

int main() {
    fast_io

    int n;
    cin >> n;
    vector<ui> mat(n, 0);
    ll ans = 0;
    do {
        ans += check(mat);
    } while(inc(mat));
    cout << ans << '\n';
}