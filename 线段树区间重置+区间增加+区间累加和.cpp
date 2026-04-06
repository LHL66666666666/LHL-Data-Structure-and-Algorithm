#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353; 
// constexpr ll MOD=1e9+7;
int T;
int n, m;
vector<ll> a;
//维护区间和
vector<ll> sum;
//维护区间增加操作的懒更新数组
vector<ll> add;
//维护区间重置的懒更新数组
vector<ll> reset;
//标记是否需要重置
vector<ll> upd;
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}
void lazy(int i, ll qv, int num, int op) {
    if (op == 1) {
        //区间增加
        sum[i] += qv * num;
        add[i] += qv;
    }
    else {
        //区间重置
        sum[i] = qv * num;
        add[i] = 0;
        reset[i] = qv;
        upd[i] = 1;
    }
}
void down(int i, int ln, int rn) {
    //根据优先级来
    //先重置
    if (upd[i] != 0) {
        lazy(i << 1, reset[i], ln, 2);
        lazy(i << 1 | 1, reset[i], rn, 2);
        upd[i] = 0;
    }
    //再增加
    if (add[i] != 0) {
        lazy(i << 1, add[i], ln, 1);
        lazy(i << 1 | 1, add[i], rn, 1);
        add[i] = 0;
    }
}
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(i);
}
void update_add(int ql, int qr, ll qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, qv, r - l + 1, 1);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        update_add(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update_add(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    up(i);
}
void update_reset(int ql, int qr, ll qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, qv, r - l + 1, 2);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        update_reset(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update_reset(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    up(i);
}
ll query(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = 0;
    if (ql <= mid) {
        ans += query(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    sum.assign((n << 2) + 1, 0);
    add.assign((n << 2) + 1, 0);
    reset.assign((n << 2) + 1, 0);
    upd.assign((n << 2) + 1, 0);
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            //区间增加操作
            int x, y;
            ll k;
            cin >> x >> y >> k;
            update_add(x, y, k, 1, n, 1);
        }
        else if (op == 2) {
            //区间重置操作
            int x, y;
            ll k;
            cin >> x >> y >> k;
            update_reset(x, y, k, 1, n, 1);
        }
        else if (op == 3) {
            int x, y;
            cin >> x >> y;
            ll ans = query(x, y, 1, n, 1);
            cout << ans << '\n';
        }
    }
    return 0;
}