#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int n, m;
int id;
constexpr int MAXN = 2e5 + 5;
vector<ll> sum(MAXN);
//×óº¢×ÓºÍÓÒº¢×Ó
vector<int> ls(MAXN);
vector<int> rs(MAXN);
vector<ll> add(MAXN);
void up(int i, int l, int r) {
    sum[i] = sum[l] + sum[r];
}
void lazy(int i, ll qv, int num) {
    add[i] += qv;
    sum[i] += qv * num;
}
void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        if (ls[i] == 0) {
            ls[i] = ++id;
        }
        if (rs[i] == 0) {
            rs[i] = ++id;
        }
        lazy(ls[i], add[i], ln);
        lazy(rs[i], add[i], rn);
        add[i] = 0;
    }
}
void update(int ql, int qr, ll qv, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        lazy(i, qv, r - l + 1);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        if (ls[i] == 0) {
            ls[i] = ++id;
        }
        update(ql, qr, qv, ls[i], l, mid);
    }
    if (qr > mid) {
        if (rs[i] == 0) {
            rs[i] = ++id;
        }
        update(ql, qr, qv, rs[i], mid + 1, r);
    }
    up(i, ls[i], rs[i]);
}
ll query(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = 0;
    if (ql <= mid) {
        if (ls[i] != 0) {
            ans += query(ql, qr, ls[i], l, mid);
        }
    }
    if (qr > mid) {
        if (rs[i] != 0) {
            ans += query(ql, qr, rs[i], mid + 1, r);
        }
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    id = 1;
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            update(l, r, k, 1, 1, n);
        }
        else {
            int l, r;
            cin >> l >> r;
            ll ans = query(l, r, 1, 1, n);
            cout << ans << '\n';
        }
    }




    return 0;
}