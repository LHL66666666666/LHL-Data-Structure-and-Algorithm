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
vector<double> a;
//维护累加和
vector<double> sum;
//维护平方和
vector<double> sq;
vector<double> add;
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    sq[i] = sq[i << 1] + sq[i << 1 | 1];
}
void lazy(int i, double qv, int num) {
    double cur = sum[i];
    sum[i] += qv * num;
    sq[i] += 2 * cur * qv + qv * qv * num;
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
        sum[i] = a[l];
        sq[i] = a[l] * a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(i);
}
void update(int ql, int qr, double qv, int l, int r, int i) {
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
double query1(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    double ans = 0;
    if (ql <= mid) {
        ans += query1(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query1(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
double query2(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return sq[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    double ans = 0;
    if (ql <= mid) {
        ans += query2(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query2(ql, qr, mid + 1, r, i << 1 | 1);
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
    sum.assign(n << 2, 0);
    add.assign(n << 2, 0);
    sq.assign(n << 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            double k;
            cin >> x >> y >> k;
            update(x, y, k, 1, n, 1);
        }
        else if (op == 2) {
            int x, y;
            cin >> x >> y;
            cout << fixed << setprecision(4) << query1(x, y, 1, n, 1) / (y - x + 1) << '\n';
        }
        else {
            int x, y;
            cin >> x >> y;
            double d1 = query2(x, y, 1, n, 1) / (y - x + 1);
            double d2 = query1(x, y, 1, n, 1) / (y - x + 1);
            cout << fixed << setprecision(4) << d1 - d2 * d2 << '\n';
        }
    }
    return 0;
}