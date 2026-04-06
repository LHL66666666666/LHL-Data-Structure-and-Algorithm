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
int n, q;
vector<ll> a;
vector<ll> mx;
vector<ll> add;
vector<ll> reset;
vector<ll> upd;
void up(int i) {
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}
void lazy(int i, ll qv, int num, int op) {
    if (op == 1) {
        mx[i] += qv;
        add[i] += qv;
    }
    else {
        mx[i] = qv;
        add[i] = 0;
        reset[i] = qv;
        upd[i] = 1;
    }
}
void down(int i, int ln, int rn) {
    if (upd[i] != 0) {
        lazy(i << 1, reset[i], ln, 2);
        lazy(i << 1 | 1, reset[i], rn, 2);
        upd[i] = 0;
    }
    if (add[i] != 0) {
        lazy(i << 1, add[i], ln, 1);
        lazy(i << 1 | 1, add[i], rn, 1);
        add[i] = 0;
    }
}
void build(int l, int r, int i) {
    if (l == r) {
        mx[i] = a[l];
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
        return mx[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = -INF;
    if (ql <= mid) {
        ans = max(ans, query(ql, qr, l, mid, i << 1));
    }
    if (qr > mid) {
        ans = max(ans, query(ql, qr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    mx.assign((n << 2), 0);
    add.assign((n << 2), 0);
    reset.assign((n << 2), 0);
    upd.assign((n << 2), 0);
    build(1, n, 1);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            update_reset(l, r, x, 1, n, 1);
        }
        else if (op == 2) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            update_add(l, r, x, 1, n, 1);
        }
        else if (op == 3) {
            int l, r;
            cin >> l >> r;
            ll ans = query(l, r, 1, n, 1);
            cout << ans << '\n';
        }
    }
    return 0;
}