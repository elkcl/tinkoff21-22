#ifndef ONPC
#pragma GCC optimize("O2")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,tune=native")
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
#include <optional>
#include <cassert>
#include <map>

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

    array<int, 6> a{};
    int k;
    for (int i : a)
        cin >> i;
    cin >> k;
    array<int, 6> ks{k / 6};
    ks[5] += k % 6;
    for (int q = 0; q < 20; ++q) {
        cout << "! ";
        for (int i = 0; i < 6; ++i)
            cout << a[i] + ks[i] << ' ';
        cout << endl;
        array<int, 6> res{};
        for (int i = 0; i < 6; ++i) {
            char c;
            cin >> c;
            if (c == '>')
                res[i] = 1;
            else if (c == '=')
                res[i] = 0;
            else
                res[i] = -1;
        }

    }

}