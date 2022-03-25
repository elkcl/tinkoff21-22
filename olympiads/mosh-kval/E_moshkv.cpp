
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
//#pragma GCC optimize("unroll-loops")

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


int32_t main() {
    fast_io
    freopen("../assets/mosh/mosh_e2.txt", "r", stdin);
    freopen("../assets/test_ans/mosh_e2_ans.txt", "w", stdout);

    int t;
    cin >> t;
    while (t--) {
        deque<int> s, q;
        bool cs = true, cq = true;
        int n;
        cin >> n;
        while (n--) {
            string tp;
            int x;
            cin >> tp >> x;
            if (tp == "push") {
                s.push_back(x);
                q.push_back(x);
            } else if (tp == "pop") {
                if (s.back() != x)
                    cs = false;
                if (q.front() != x)
                    cq = false;
                s.pop_back();
                q.pop_front();
            }
        }
        if (cs && cq)
            cout << "both\n";
        else if (cs)
            cout << "stack\n";
        else if (cq)
            cout << "queue\n";
        else
            cout << "none\n";
    }
}