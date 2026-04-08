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
int n, m;
//关键点：一个数字模上比自身大的数字，等于不操作
//一个数字模上比自己小的数字，每次至少削减一半(至少变为原来的1/2)
//因此每个数字X的取模次数最多logX次，可以暴力修改+剪枝
//另外：操作3是单点修改，每次操作3最多增加一个点的势能，增加有限
vector<ll> a;
vector<ll> sum;
vector<ll> mx;
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}
void update_reset(int ql, int qr, ll qv, int l, int r, int i) {
    if (l == r) {
        mx[i] = qv;
        sum[i] = qv;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update_reset(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update_reset(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    up(i);
}
void update_mod(int ql, int qr, ll mod, int l, int r, int i) {
    if (l == r) {
        sum[i] %= mod;
        mx[i] %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid && mx[i << 1] >= mod) {
        update_mod(ql, qr, mod, l, mid, i << 1);
    }
    if (qr > mid && mx[i << 1 | 1] >= mod) {
        update_mod(ql, qr, mod, mid + 1, r, i << 1 | 1);
    }
    up(i);
}
ll query(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    int mid = (r + l) >> 1;
    ll ans = 0;
    if (ql <= mid) {
        ans += query(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = a[l];
        mx[i] = a[l];
        return;
    }
    int mid = (r + l) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(i);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    a.assign(n + 1, 0);
    sum.assign((n << 2), 0);
    mx.assign((n << 2), 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            ll ans = query(l, r, 1, n, 1);
            cout << ans << '\n';
        }
        else if (op == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            update_mod(l, r, x, 1, n, 1);
        }
        else {
            int k, x;
            cin >> k >> x;
            update_reset(k, k, x, 1, n, 1);
        }
    }
    return 0;
}