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
#include <unordered_map>

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

struct Drink {
    unordered_map<int, int> ingrs;
    bool avail = true;
};


int main() {
    fast_io

    int m, n, k;
    unordered_map<string, int> ing_c, dri_c;

    cin >> m;
    vi ing(m);
    for (int i = 0; i < m; ++i) {
        string s;
        int x;
        cin >> s >> x;
        ing[i] = x;
        ing_c[s] = i;
    }

    cin >> n;
    vector<Drink> dri(n);
    int cnt = n;
    for (int i = 0; i < n; ++i) {
        string s;
        int r;
        cin >> s >> r;
        dri_c[s] = i;
        for (int j = 0; j < r; ++j) {
            string vs;
            int x;
            cin >> vs >> x;
            int v = ing_c[vs];
            dri[i].ingrs[v] = x;
            if (x > ing[v] && dri[i].avail) {
                dri[i].avail = false;
                --cnt;
            }
        }
    }

    cin >> k;
    cout << cnt << '\n';
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        int d = dri_c[s];
        for (auto &el : dri[d].ingrs) {
            ing[el.first] -= el.second;
        }
        for (int j = 0; j < n; ++j) {
            if (!dri[j].avail)
                continue;
            for (auto &el : dri[j].ingrs) {
                if (el.second > ing[el.first]) {
                    dri[j].avail = false;
                    --cnt;
                    break;
                }
            }
        }
        cout << cnt << '\n';
    }
}