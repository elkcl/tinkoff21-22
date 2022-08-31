#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int mxn = 1e5 + 10;

struct SegmentTree {
public:
    void init(vector<int> a) {
        size = a.size();
        fill(added, added+4*mxn, 0);
        build(a, 0, 0, size);
    }
    void add(int l, int r, long long v) {
        add(l, r, v, 0, 0, size);
    }
    long long get(int l, int r) {
        return get(l, r, 0, 0, size, 0);
    }
private:
    int size;
    long long tree[4*mxn];
    long long added[4*mxn];
    void build(vector<int>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = a[lx];
            return;
        }

        int m = (rx + lx) / 2;

        build(a, 2*x+1, lx, m);
        build(a, 2*x+2, m, rx);

        tree[x] = tree[2*x+1] + tree[2*x+2];
    }
    void add(int l, int r, long long v, int x, int lx, int rx) {
        if (r <= lx || rx <= l) return;
        if (l <= lx && rx <= r) {
            added[x] += v;
            return;
        }

        int m = (rx + lx) / 2;

        add(l, r, v, 2*x+1, lx, m);
        add(l, r, v, 2*x+2, m, rx);

        tree[x] = tree[2*x+1] + tree[2*x+2] + added[2*x+1] * (long long)(m - lx) + added[2*x+2] * (long long)(rx - m);
    }
    long long get(int l, int r, int x, int lx, int rx, long long current_added) {
        if (r <= lx || rx <= l) return 0;
        current_added += added[x];
        if (l <= lx && rx <= r) {
            return tree[x] + (long long)(rx - lx) * current_added;
        }
        int m = (lx + rx) / 2;
        return get(l, r, 2*x+1, lx, m, current_added) + get(l, r, 2*x+2, m, rx, current_added);
    }
};

SegmentTree st;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    st.init(a);
    for (int i = 0; i < m; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            int v;
            cin >> v;
            st.add(l, r, v);
        } else {
            cout << st.get(l, r) << endl;
        }
    }
    return 0;
}