#include <bits/stdc++.h>
using namespace std;
struct el{
    int val, mod;
    explicit el (int _val = 0, int _mod = 0){
        val = _val;
        mod = _mod;
    }
};
el mx (el a, el b){
    if (a.val + a.mod >= b.val + b.mod) return a;
    else return b;
}
vector<int> tree;
vector<int> mod;
// o(n)
void build(int a[], int v, int vl, int vr){
    if (v == 0){
        tree.resize(4 * vr);
        mod.resize(4 * vr, 0);
    }
    if (vr - vl == 1){
        tree[v] = a[vl];
        return;
    }
    int m = (vl + vr) / 2;
    build(a, v * 2 + 1, vl, m);
    build(a, v * 2 + 2, m, vr);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}
// lazy propagation
void push(int v){
    if (2 * v + 1 < tree.size()){
        mod[2 * v + 1] += mod[v];
    }
    if (2 * v + 2 < tree.size()){
        mod[2 * v + 2] += mod[v];
    }
    tree[v] += mod[v];
    mod[v] = 0;
}

int fresh(int v) {
    return tree[v] + mod[v];
}
// mass update +=
void update(int v, int vl, int vr, int l, int r, int x){
    if (vl >= l && vr <= r){
        mod[v] += x;
        //push(v);
        return;
    }
    if (vl >= r || vr <= l){
        //push(v);
        return;
    }
    push(v);
    update(2 * v + 1, vl, (vl + vr) / 2, l, r, x);
    update(2 * v + 2, (vl + vr) / 2, vr, l, r, x);
    tree[v] = max(fresh(2 * v + 1), fresh(2 * v + 2));
}
// for speed up
/*
void update_single(int v, int vl, int vr, int pos, int x){
    //push(v);
    if (vr - vl == 1) {
        tree[v].mod += x;
        //push(v);
        return;
    }
    push(v);
    int vm = (vl + vr) / 2;
    if (pos < vm) {
        update_single(2 * v + 1, vl, vm, pos, x);
    } else {
        update_single(2 * v + 2, vm, vr, pos, x);
    }
    tree[v] = mx(tree[2 * v + 1], tree[2 * v + 2]);
}*/

// max on substring
int get(int v, int vl, int vr, int l, int r){
    //push(v);
    if (vl >= l && vr <= r){
        return fresh(v);
    }
    if (vl >= r || vr <= l){
        return -2000000000;
    }
    push(v);
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

                update(0, 0, n, l - 1, r, x);

        }
        else{
            cin >> l >> r;
            cout << get(0, 0, n, l - 1, r) << " ";
        }
    }
}
