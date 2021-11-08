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

const int ALPHABET = 26;
const char BASE = 'a';

/*struct PairHash {
    size_t operator()(const ii &p) const {
        ll a = p.first;
        ll b = p.second;
        a <<= 32;
        auto h = hash<ll>{};
        return h(a + b);
    }
};*/

struct Node {
    array<int, ALPHABET> next{};
    bool term = false;
};

struct Trie {
    vector<Node> nodes;

    Trie() {
        nodes.reserve(260000);
        nodes.emplace_back();
    }

    int create_node() {
        nodes.emplace_back();
        return static_cast<int>(nodes.size() - 1);
    }

    void insert(const string &s) {
        int v = 0;
        for (char c : s) {
            c -= BASE;
            if (!nodes[v].next[c])
                nodes[v].next[c] = create_node();
            v = nodes[v].next[c];
        }
        nodes[v].term = true;
    }

    void sorted_rec(vector<string> &out, int v) {
        if (nodes[v].term)
            out.push_back(out.back());
        for (int i = 0; i < ALPHABET; ++i) {
            if (nodes[v].next[i]) {
                out.back() += static_cast<char>(i + BASE);
                sorted_rec(out, nodes[v].next[i]);
                out.back().pop_back();
            }
        }
    }

    void sorted(vector<string> &out) {
        out.emplace_back();
        sorted_rec(out, 0);
        out.pop_back();
    }
};

void trav(vector<vc> &fld, Trie &tr, string &curr, Trie &ans, vector<vc> &used, int n, int m, int x, int y, int v) {
    int c = fld[x][y] - BASE;
    if (!tr.nodes[v].next[c]) {
        return;
    }
    v = tr.nodes[v].next[c];
    used[x][y] = true;
    curr += static_cast<char>(c + BASE);
    if (tr.nodes[v].term)
        ans.insert(curr);
    if (x > 0 && !used[x - 1][y]) {
        trav(fld, tr, curr, ans, used, n, m, x - 1, y, v);
    }
    if (y > 0 && !used[x][y - 1]) {
        trav(fld, tr, curr, ans, used, n, m, x, y - 1, v);
    }
    if (x < n - 1 && !used[x + 1][y]) {
        trav(fld, tr, curr, ans, used, n, m, x + 1, y, v);
    }
    if (y < m - 1 && !used[x][y + 1]) {
        trav(fld, tr, curr, ans, used, n, m, x, y + 1, v);
    }
    used[x][y] = false;
    curr.pop_back();
}

int main() {
    fast_io

    int n, m, d;
    cin >> n >> m;
    vector<vc> fld(n, vc(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> fld[i][j];
        }
    }

    Trie tr;
    cin >> d;
    for (int i = 0; i < d; ++i) {
        string s;
        cin >> s;
        tr.insert(s);
    }

    string curr;
    Trie ans;
    vector<vc> used(n, vc(m, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            trav(fld, tr, curr, ans, used, n, m, i, j, 0);
        }
    }

    vector<string> ansv;
    ans.sorted(ansv);
    cout << ansv.size() << '\n';
    for (auto &s : ansv)
        cout << s << '\n';
}