#include <bits/stdc++.h>
using namespace std;
struct el{
    int val, mod;
    el (int _val = 0, int _mod = 0){
        val = _val;
        mod = _mod;
    }
};
el mx (el a, el b){
    if (a.val >= b.val) return a;
    else return b;
}
vector<el> tree;
// o(n)
void build(int a[], int v, int vl, int vr){
    if (v == 0){
        tree.resize(4 * vr);
    }
    if (vr - vl == 1){
        tree[v] = el(a[vl], 0);
        return;
    }
    int m = (vl + vr) / 2;
    build(a, v * 2 + 1, vl, m);
    build(a, v * 2 + 2, m, vr);
    tree[v] = mx(tree[2 * v + 1], tree[2 * v + 2]);
}
// lazy propagation
void push(int v){
    if (2 * v + 1 < tree.size()){
        tree[2 * v + 1].mod += tree[v].mod;
    }
    if (2 * v + 2 < tree.size()){
        tree[2 * v + 2].mod += tree[v].mod;
    }
    tree[v].val += tree[v].mod;
    tree[v].mod = 0;
}
// mass update +=
void update(int v, int vl, int vr, int l, int r, int x){
    if (vl >= l && vr <= r){
        tree[v].mod += x;
        push(v);
        return;
    }
    if (vl >= r || vr <= l){
        push(v);
        return;
    }
    push(v);
    update(2 * v + 1, vl, (vl + vr) / 2, l, r, x);
    update(2 * v + 2, (vl + vr) / 2, vr, l, r, x);
    tree[v] = mx(tree[2 * v + 1], tree[2 * v + 2]);
}
// for speed up
void update_single(int v, int vl, int vr, int pos, int x){ 
    push(v);
    if (vr - vl == 1) {
        tree[v].mod += x;
        push(v);
        return;
    }
    int vm = (vl + vr) / 2;
    if (pos < vm) {
        update_single(2 * v + 1, vl, vm, pos, x);
    } else {
        update_single(2 * v + 2, vm, vr, pos, x);
    }
    tree[v] = mx(tree[2 * v + 1], tree[2 * v + 2]);
}
// max on substring
int get(int v, int vl, int vr, int l, int r){
    push(v);
    if (vl >= l && vr <= r){
        return tree[v].val;
    }
    if (vl >= r || vr <= l){
        return -2000000000;
    }
    return max(get(2 * v + 2, (vl + vr) / 2, vr, l, r), get(2 * v + 1, vl, (vl + vr) / 2, l, r));
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n = 0;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    build(a, 0, 0, n);
    int k = 0;
    cin >> k;
    char c;
    int l = 0, r = 0, x = 0;
    for (int i = 0; i < k; i++){
        cin >> c;
        if (c == 'a'){
            cin >> l >> r >> x;
            if (l == r) {
                update_single(0, 0, n, l - 1, x);
            } else {
                update(0, 0, n, l - 1, r, x);
            }
        }
        else{
            cin >> l >> r;
            cout << get(0, 0, n, l - 1, r) << " ";
        }
    }
}
