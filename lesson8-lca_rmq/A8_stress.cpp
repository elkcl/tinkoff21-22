#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

/*
 ⠄⠄⠄⢰⣧⣼⣯⠄⣸⣠⣶⣶⣦⣾⠄⠄⠄⠄⡀⠄⢀⣿⣿⠄⠄⠄⢸⡇⠄⠄
⠄⠄⠄⣾⣿⠿⠿⠶⠿⢿⣿⣿⣿⣿⣦⣤⣄⢀⡅⢠⣾⣛⡉⠄⠄⠄⠸⢀⣿⠄
⠄⠄⢀⡋⣡⣴⣶⣶⡀⠄⠄⠙⢿⣿⣿⣿⣿⣿⣴⣿⣿⣿⢃⣤⣄⣀⣥⣿⣿⠄
⠄⠄⢸⣇⠻⣿⣿⣿⣧⣀⢀⣠⡌⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⣿⣿⣿⠄
⠄⢀⢸⣿⣷⣤⣤⣤⣬⣙⣛⢿⣿⣿⣿⣿⣿⣿⡿⣿⣿⡍⠄⠄⢀⣤⣄⠉⠋⣰
⠄⣼⣖⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⢇⣿⣿⡷⠶⠶⢿⣿⣿⠇⢀⣤
⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⡇⣿⣿⣿⣿⣿⣿⣷⣶⣥⣴⣿⡗
⢀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠄
⢸⣿⣦⣌⣛⣻⣿⣿⣧⠙⠛⠛⡭⠅⠒⠦⠭⣭⡻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠄
⠘⣿⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⠄⠄⠄⠄⠄⠹⠈⢋⣽⣿⣿⣿⣿⣵⣾⠃⠄
⠄⠘⣿⣿⣿⣿⣿⣿⣿⣿⠄⣴⣿⣶⣄⠄⣴⣶⠄⢀⣾⣿⣿⣿⣿⣿⣿⠃⠄⠄
⠄⠄⠈⠻⣿⣿⣿⣿⣿⣿⡄⢻⣿⣿⣿⠄⣿⣿⡀⣾⣿⣿⣿⣿⣛⠛⠁⠄⠄⠄
⠄⠄⠄⠄⠈⠛⢿⣿⣿⣿⠁⠞⢿⣿⣿⡄⢿⣿⡇⣸⣿⣿⠿⠛⠁⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠉⠻⣿⣿⣾⣦⡙⠻⣷⣾⣿⠃⠿⠋⠁⠄⠄⠄⠄⠄⢀⣠⣴
⣿⣿⣿⣶⣶⣮⣥⣒⠲⢮⣝⡿⣿⣿⡆⣿⡿⠃⠄⠄⠄⠄⠄⠄⠄⣠⣴⣿⣿⣿
*/
#define all(a) a.begin(), a.end()
#define FNAME ""
#define int ll
typedef pair<int, int> pii;
#define _ << ' ' <<
#define vec vector
#ifndef HOME
#define cerr \
    if (0) cerr
#endif
#define print(a) (cerr << "Line:" _ __LINE__ << ", Name:" _ #a << ", Value:" _ a << '\n')

bool chkmax(int &a, int b, bool eq = false) {
    if (a < b) {
        a = b;
        return true;
    }
    return a == b && eq;
}
bool chkmin(int &a, int b, bool eq = false) {
    if (a > b) {
        a = b;
        return true;
    }
    return a == b && eq;
}
#ifdef int
const int INF = 2e16;
#else
const int INF = 2e9;
#endif

mt19937 gen(time(0));
const int MAXN = 3e5;
const int MAXL = 20;
vec<int> g[MAXN];
int h[MAXN];
int binup[MAXL][MAXN];
void dfs(int v, int p) {
    for (auto to : g[v]) {
        if (to == p) continue;
        binup[0][to] = v;
        h[to] = h[v] + 1;
        dfs(to, v);
    }
}
void build() {
    for (int i = 1; i < MAXL; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            binup[i][j] = binup[i - 1][binup[i - 1][j]];
        }
    }
}
int lca(int a, int b) {
    if (h[a] < h[b]) swap(a, b);
    int d = h[a] - h[b];
    for (int i = 0; i < MAXL; ++i) {
        if (d & (1 << i)) {
            a = binup[i][a];
        }
    }
    if (a == b) return a;
    for (int i = MAXL - 1; i >= 0; --i) {
        int na = binup[i][a];
        int nb = binup[i][b];
        if (na != nb) {
            a = na;
            b = nb;
        }
    }
    return binup[0][a];
}
int dop[MAXN];
int offtop = 0;
int ans[MAXN];
void dfs2(int v, int p, int up) {
    up+= dop[v];
    ans[v] = up;
    for (auto to: g[v]) {
        if (to == p) continue;
        dfs2(to, v, up);
    }
}
void solve() {
    //code here
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);
    build();
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        int l = lca(u, v);
        if (l == v || l == u) {
            if (h[u] < h[v]) swap(u, v);
            dop[u]++;
            int d = h[u] - h[v];
            d--;
            for (int i = 0; i < MAXL; ++i) {
                if (d & (1 << i)) {
                    u = binup[i][u];
                }
            }
            dop[u] -=1;
            offtop++;
        } else {
            dop[u]++;
            dop[v]++;
        }
    }
    dfs2(1, -1, offtop);
    int  mn = 0;
    for (int i = 1; i <= n; ++i) {
        mn = max(mn, ans[i]);
    }
    cout << mn;

    //
}

signed main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    //freopen("input.txt", "w", stdout);
#else
    if (FNAME != "") {
        freopen(FNAME ".in", "r", stdin);
        freopen(FNAME ".out", "w", stdout);
    }
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //    cin >> tt;
    for (int req = 0; req < tt; ++req) {
        unsigned start = clock();
        solve();
        cout << '\n';
        unsigned end = clock();
        cerr << "WorkTime: " << (end - start) / (double) CLOCKS_PER_SEC << '\n';
    }
}