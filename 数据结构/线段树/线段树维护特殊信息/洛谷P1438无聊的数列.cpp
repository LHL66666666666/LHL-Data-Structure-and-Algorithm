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
vector<ll> a;
//使用差分数组构建线段树
vector<ll> d;
vector<ll> add;
void up(int i) {
    d[i] = d[i << 1] + d[i << 1 | 1];
}
void lazy(int i, ll qv, int num) {
    d[i] += 1LL * qv * num;
    add[i] += qv;
}
void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        lazy(i << 1, add[i], ln);
        lazy(i << 1 | 1, add[i], rn);
        add[i] = 0;
    }
}
void build(int l, int r, int i) {
    if (l == r) {
        d[i] = a[l] - a[l - 1];
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
        return d[i];
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
    a.assign(n + 1, 0);
    d.assign(n << 2, 0);
    add.assign(n << 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, K, D;
            cin >> l >> r >> K >> D;
            update(l, l, K, 1, n, 1);
            if (l + 1 <= r) update(l + 1, r, D, 1, n, 1);
            if (r + 1 <= n) update(r + 1, r + 1, -1LL * (K + (r - l) * D), 1, n, 1);
        }
        else {
            int p;
            cin >> p;
            ll ans = query(1, p, 1, n, 1);
            cout << ans << '\n';
        }
    }




    return 0;
}