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
//本题不能使用懒标记，因为子节点的修改无法再O(1)时间内改到父节点上
//但是1e12的数字，最多开6次平方根就变为1了
//可以剪枝：对于最大值为1的区间，无需再操作
//处理操作时，需要对每一个子节点暴力开平方修改
//区间累加和
vector<ll> sum;
//区间最大值
vector<ll> mx;
vector<ll> a;
void update(int ql, int qr, int l, int r, int i) {
    if (l == r) {
        sum[i] = (ll)sqrt(sum[i]);
        mx[i] = (ll)sqrt(mx[i]);
        return;
    }
    int mid = (r + l) >> 1;
    if (ql <= mid) {
        if (mx[i << 1] > 1) {
            update(ql, qr, l, mid, i << 1);
        }
    }
    if (qr > mid) {
        if (mx[i << 1 | 1] > 1) {
            update(ql, qr, mid + 1, r, i << 1 | 1);
        }
    }
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}
ll query1(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    int mid = (r + l) >> 1;
    ll ans = 0;
    if (ql <= mid) {
        ans += query1(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query1(ql, qr, mid + 1, r, i << 1 | 1);
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
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sum.assign(n << 2, 0);
    mx.assign(n << 2, 0);
    build(1, n, 1);
    cin >> m;
    while (m--) {
        int op;
        cin >> op;
        int l, r;
        cin >> l >> r;
        if (l > r) swap(l, r);
        if (op == 0) {
            update(l, r, 1, n, 1);
        }
        else {
            ll ans = query1(l, r, 1, n, 1);
            cout << ans << '\n';
        }

    }
    return 0;
}