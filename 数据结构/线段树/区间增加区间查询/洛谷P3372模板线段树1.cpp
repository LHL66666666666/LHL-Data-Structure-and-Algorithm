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
//维护区间和的线段树
vector<ll> sum;
//维护懒标记的数组
vector<ll> add;
//up方法表示使用子节点信息更新这个节点的信息
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}
//lazy方法用于打上懒标记
void lazy(int i, ll qv, int num) {
    sum[i] += 1LL * qv * num;
    add[i] += 1LL * qv;
}
//down方法用于下发懒标记
void down(int i, int ln, int rn) {
    //如果有懒标记才下发
    if (add[i] != 0) {
        //左孩子
        lazy(i << 1, add[i], ln);
        //右孩子
        lazy(i << 1 | 1, add[i], rn);
        //清空自身的懒信息
        add[i] = 0;
    }
}
//建树
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    //左孩子
    build(l, mid, i << 1);
    //右孩子
    build(mid + 1, r, i << 1 | 1);
    up(i);
}
//区间修改，区间[ql,qr]范围上全加qv
//当前所处的区间是[l,r],编号为i
void update(int ql, int qr, ll qv, int l, int r, int i) {
    //base case:当任务区间包含当前区间时(全包),不用继续向下更新了，
    //在这里懒更新标记,同时更新区间和数组
    if (ql <= l && r <= qr) {
        lazy(i, qv, r - l + 1);
        return;
    }
    //不全包,首先要将懒标记下发到左右孩子
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    //递归处理
    if (ql <= mid) {
        update(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    //更新自己
    up(i);
}
//区间查询
ll query(int ql, int qr, int l, int r, int i) {
    //base case:当任务区间包含当前区间时(全包),不用继续向下查询了,直接返回
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    //如果不全包，首先将懒标记下发到左右孩子,因为懒标记上有子节点的更新信息
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
    //注意，这里因为没有修改任何一个数字，因此不需要up方法来修正
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    sum.assign((n << 2) + 1, 0);
    add.assign((n << 2) + 1, 0);
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