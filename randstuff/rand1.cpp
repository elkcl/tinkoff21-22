#define HOME

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
using namespace std;
typedef long long ll;
typedef long double ld;

/*
⣿⣿⣷⡁⢆⠈⠕⢕⢂⢕⢂⢕⢂⢔⢂⢕⢄⠂⣂⠂⠆⢂⢕⢂⢕⢂⢕⢂⢕⢂
⣿⣿⣿⡷⠊⡢⡹⣦⡑⢂⢕⢂⢕⢂⢕⢂⠕⠔⠌⠝⠛⠶⠶⢶⣦⣄⢂⢕⢂⢕
⣿⣿⠏⣠⣾⣦⡐⢌⢿⣷⣦⣅⡑⠕⠡⠐⢿⠿⣛⠟⠛⠛⠛⠛⠡⢷⡈⢂⢕⢂
⠟⣡⣾⣿⣿⣿⣿⣦⣑⠝⢿⣿⣿⣿⣿⣿⡵⢁⣤⣶⣶⣿⢿⢿⢿⡟⢻⣤⢑⢂
⣾⣿⣿⡿⢟⣛⣻⣿⣿⣿⣦⣬⣙⣻⣿⣿⣷⣿⣿⢟⢝⢕⢕⢕⢕⢽⣿⣿⣷⣔
⣿⣿⠵⠚⠉⢀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣗⢕⢕⢕⢕⢕⢕⣽⣿⣿⣿⣿
⢷⣂⣠⣴⣾⡿⡿⡻⡻⣿⣿⣴⣿⣿⣿⣿⣿⣿⣷⣵⣵⣵⣷⣿⣿⣿⣿⣿⣿⡿
⢌⠻⣿⡿⡫⡪⡪⡪⡪⣺⣿⣿⣿⣿⣿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃
⠣⡁⠹⡪⡪⡪⡪⣪⣾⣿⣿⣿⣿⠋⠐⢉⢍⢄⢌⠻⣿⣿⣿⣿⣿⣿⣿⣿⠏⠈
⡣⡘⢄⠙⣾⣾⣾⣿⣿⣿⣿⣿⣿⡀⢐⢕⢕⢕⢕⢕⡘⣿⣿⣿⣿⣿⣿⠏⠠⠈
⠌⢊⢂⢣⠹⣿⣿⣿⣿⣿⣿⣿⣿⣧⢐⢕⢕⢕⢕⢕⢅⣿⣿⣿⣿⡿⢋⢜⠠⠈
⠄⠁⠕⢝⡢⠈⠻⣿⣿⣿⣿⣿⣿⣿⣷⣕⣑⣑⣑⣵⣿⣿⣿⡿⢋⢔⢕⣿⠠⠈
⠨⡂⡀⢑⢕⡅⠂⠄⠉⠛⠻⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⢔⢕⢕⣿⣿⠠⠈
⠄⠪⣂⠁⢕⠆⠄⠂⠄⠁⡀⠂⡀⠄⢈⠉⢍⢛⢛⢛⢋⢔⢕⢕⢕⣽⣿⣿⠠⠈
*/
#define all(a) a.begin(), a.end()
#define FNAME ""
//#define int ll
typedef pair<int, int> pii;
#define _ << ' ' <<
#define vec vector
#ifndef HOME
#define cerr \
    if (0) cerr
#endif

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
const int MAXN = 1e5 + 123;
//set<int> st;
struct Node {
    int l, r;
    int ind;
};
Node nd[MAXN];
int rest[MAXN];
int lst = 1;
int nn() {
    return lst++;
}
int f[MAXN];
int lf[MAXN];
int rg[MAXN];
int a[MAXN];
void solve() {
    //code here
    int n, k;
    cin >> n >> k;

    vec<pii> vc(n);
    //vc.resize(n);
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a[i + 1] = x;
        vc[pos++]={-x, i + 1};
    }
    {
        stack<pii> st;
        st.push({INF, -1});
        for (int i = 1; i <= n; ++i) {
            while (st.top().first < a[i]) {
                st.pop();
            }
            lf[i] = st.top().second;
            st.push({a[i], i});
        }

    }
    {
        stack<pii> st;
        st.push({INF, -1});
        for (int i = n; i >= 1; --i) {
            while (st.top().first <= a[i]) {
                st.pop();
            }
            rg[i] = st.top().second;
            st.push({a[i], i});
        }

    }
    sort(all(vc));
    ll ans =0 ;

    for (auto [X, i]: vc) {
        X = -X;
//        st.insert(i);
        int ind = nn();
        rest[i] = ind;
        if (lf[i] != -1) {
            int l = rest[lf[i]];
            nd[ind].l = l;
            nd[l].r = ind;
        } else {
            nd[ind].l = -1;
        }
        if (rg[i] != -1) {
            int r = rest[rg[i]];
            nd[ind].r = r;
            nd[r].l = ind;
        } else {
            nd[ind].r = -1;
        }
        nd[ind].ind = i;
//        for (int i = 0; i < 2 * k + 10; ++i) {
//            f[i] = -1;
//        }

        int fi= k + 1;
        f[k] = i;
        int indf = nd[ind].r;
        for (int j = 0; j < k - 1; ++j) {
            if (indf == -1) break;
            f[fi++] = (nd[indf].ind);
            indf= nd[indf].r;
        }

        if (indf == -1) {
            f[fi]=n + 1;
        } else {
            f[fi]= (nd[indf].ind);
        }
        int forw = fi --;

        fi = k - 1;
        for (int j = 0; j < k - 1; ++j) {
            if (nd[ind].l == -1) break;
            ind = nd[ind].l;
            f[fi--] = (nd[ind].ind);
        }

        int back = fi + 1;
        if (nd[ind].l == -1 ) {
            f[fi] = 0;
        } else {
            ind = nd[ind].l;
            f[fi] = nd[ind].ind;
        }
        forw = min(forw - k, k);
        for (int i = back; i <= forw; ++i) {
            int j = i + k;
            int c = f[i] - f[i - 1];
            int d = f[j] - f[j - 1];
            ans += 1ll * c * d * X;
        }
    }
    cout << ans << '\n';
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

        unsigned end = clock();
        cout << "WorkTime: " << (end - start) / (double) CLOCKS_PER_SEC << '\n';
        cout << '\n';

    }
}