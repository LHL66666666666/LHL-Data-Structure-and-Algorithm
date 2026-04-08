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
//维护最大值的线段树
vector<ll> mx;
//懒标记
vector<ll> add;
//是否有懒标记的标记数组
vector<int> upd;
void up(int i) {
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}
void lazy(int i, ll qv, int num) {
    mx[i] = qv;
    add[i] = qv;
    upd[i] = 1;
}
void down(int i, int ln, int rn) {
    if (upd[i] != 0) {
        lazy(i << 1, add[i], ln);
        lazy(i << 1 | 1, add[i], rn);
        upd[i] = 0;
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
void update(int ql, int qr, ll qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, qv, r - l + 1);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        update(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update(ql, qr, qv, mid + 1, r, i << 1 | 1);
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
    cin >> n >> m;
    mx.assign((n << 2) + 1, 0);
    add.assign((n << 2) + 1, 0);
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
            int x, y;
            ll k;
            cin >> x >> y >> k;
            update(x, y, k, 1, n, 1);
        }
        else if (op == 2) {
            int x, y;
            cin >> x >> y;
            ll ans = query(x, y, 1, n, 1);
            cout << ans << '\n';
        }
    }
    return 0;
}