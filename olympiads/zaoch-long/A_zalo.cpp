#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2")
#pragma GCC optimize("unroll-loops")
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

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct cool {
    vector<int> v;
    int i = 0;

    bool empty() const {
        return v.empty() || i >= v.size();
    }

    int front() const {
        return *(v.begin() + i);
    }
};

bool update(vector<cool> &pos, vi &b) {
    if (pos[b[0]].empty())
        return false;
    int last = pos[b[0]].front();
    for (auto i : b) {
        if (!pos[i].empty() && last > pos[i].front())
            pos[i].i = lower_bound(pos[i].v.begin() + pos[i].i, pos[i].v.end(), last) - pos[i].v.begin();
        if (pos[i].empty())
            return false;
        last = pos[i].front();
    }
    return true;
}


int main() {
    fast_io

    int n, m;
    cin >> n >> m;
    vi a(n), b(m), r(n, -1);
    for (int &i : a)
        cin >> i;
    for (int &i : b)
        cin >> i;

    unordered_set<int> isb(all(b));
    vector<cool> pos(200'001);
    for (int i = 0; i < n; ++i) {

        pos[a[i]].v.push_back(i);
    }
    if (!update(pos, b)) {
        for (int i : r)
            cout << i << ' ';
        cout << '\n';
        return 0;
    }
    r[0] = pos[b.back()].front() + 1;
    for (int i = 1; i < n; ++i) {
        if (i <= pos[b[0]].front()) {
            r[i] = r[i-1];
            continue;
        }
        if (!pos[b[0]].empty() && i > pos[b[0]].front())
            pos[b[0]].i = lower_bound(pos[b[0]].v.begin() + pos[b[0]].i, pos[b[0]].v.end(), i) - pos[b[0]].v.begin();
        if (update(pos, b)) {
            r[i] = pos[b.back()].front() + 1;
        } else {
            for (int i : r)
                cout << i << ' ';
            cout << '\n';
            return 0;
        }
    }
    for (int i : r)
        cout << i << ' ';
    cout << '\n';
    return 0;
}