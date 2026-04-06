#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int T;
int n, m;
vector<ll> a;
//累加和
vector<ll> sum;
//最大值
vector<ll> mx;
//最大值的个数
vector<ll> cnt;
//次大值
vector<ll> sec;
void up(int i) {
    int l = i << 1, r = i << 1 | 1;
    //汇总累加和
    sum[i] = sum[l] + sum[r];
    //汇总最大值，次大值信息
    //分类讨论
    if (mx[l] > mx[r]) {
        mx[i] = mx[l];
        cnt[i] = cnt[l];
        sec[i] = max(sec[l], mx[r]);
    }
    else if (mx[l] < mx[r]) {
        mx[i] = mx[r];
        cnt[i] = cnt[r];
        sec[i] = max(sec[r], mx[l]);
    }
    else {
        mx[i] = mx[l];
        cnt[i] = cnt[l] + cnt[r];
        sec[i] = max(sec[l], sec[r]);
    }
}
void build(int i, int l, int r) {
    if (l == r) {
        sum[i] = a[l];
        mx[i] = a[l];
        cnt[i] = 1;
        sec[i] = -INF;
        return;
    }
    int mid = (r + l) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    up(i);
}
void lazy(int i, ll qv) {
    sum[i] -= (mx[i] - qv) * cnt[i];
    mx[i] = qv;
}
void down(int i) {
    //将最大值下发
    //父亲范围上懒更新任务的下发不会颠覆孩子的次大值
    //因为如果会颠覆的话，父节点必定在修改阶段就下发了
    int l = i << 1, r = i << 1 | 1;
    if (mx[i] < mx[l]) lazy(l, mx[i]);
    if (mx[i] < mx[r]) lazy(r, mx[i]);
}
void setmin(int ql, int qr, ll qv, int i, int l, int r) {
    if (qv >= mx[i]) {
        //大于最大值，不操作
        return;
    }
    //比最大值小
    if (ql <= l && r <= qr && qv > sec[i]) {
        //全包，且比次大值还大
        lazy(i, qv);
        return;
    }
    //到左右孩子去
    int mid = (r + l) >> 1;
    down(i);
    if (ql <= mid) {
        setmin(ql, qr, qv, i << 1, l, mid);
    }
    if (qr > mid) {
        setmin(ql, qr, qv, i << 1 | 1, mid + 1, r);
    }
    up(i);
}
ll query1(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return mx[i];
    int mid = (r + l) >> 1;
    down(i);
    ll ans = -INF;
    if (ql <= mid) {
        ans = max(ans, query1(ql, qr, i << 1, l, mid));
    }
    if (qr > mid) {
        ans = max(ans, query1(ql, qr, i << 1 | 1, mid + 1, r));
    }
    return ans;
}
ll query2(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return sum[i];
    int mid = (r + l) >> 1;
    down(i);
    ll ans = 0;
    if (ql <= mid) {
        ans += query2(ql, qr, i << 1, l, mid);
    }
    if (qr > mid) {
        ans += query2(ql, qr, i << 1 | 1, mid + 1, r);
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        sum.assign(n << 2, 0);
        mx.assign(n << 2, 0);
        cnt.assign(n << 2, 0);
        sec.assign(n << 2, 0);
        build(1, 1, n);
        while (m--) {
            int op;
            cin >> op;
            if (op == 0) {
                int x, y;
                ll t;
                cin >> x >> y >> t;
                setmin(x, y, t, 1, 1, n);
            }
            else if (op == 1) {
                int x, y;
                cin >> x >> y;
                ll ans = query1(x, y, 1, 1, n);
                cout << ans << '\n';
            }
            else if (op == 2) {
                int x, y;
                cin >> x >> y;
                ll ans = query2(x, y, 1, 1, n);
                cout << ans << '\n';
            }
        }
    }
    return 0;
}