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
int n;
vector<ll> y = { -INF };
struct node {
    ll x1, y1, x2, y2;
};
struct event {
    ll x, d;
    ll y1, y2;
    bool operator<(const event& other)const {
        return x < other.x;
    }
};
vector<node> a;
//线段树维护三个信息:区间长度，区间被覆盖的长度，覆盖次数
//无需懒标记，因为每个矩形有区间+1，后面必有与之对应的区间-1操作
vector<ll> len;
vector<ll> cover;
vector<ll> cnt;
void up(int i, int l, int r) {
    if (cnt[i] > 0) {
        cover[i] = len[i];
    }
    else if (l == r) {
        //叶节点直接设置cover
        //否则会越界
        cover[i] = 0;
    }
    else cover[i] = cover[i << 1] + cover[i << 1 | 1];
}
void build(int i, int l, int r) {
    if (l == r) {
        len[i] = y[l + 1] - y[l];
        return;
    }
    len[i] = y[r + 1] - y[l];
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
}
//这个题的特殊性在于
//1) 查询操作永远查的是整个范围，不会有小范围的查询，每次都返回cover[1]
//2) 增加操作之后，后续一定会有等规模的减少操作
//根据以上两点分析出不需要懒更新机制
//首先当一次修改完成从下往上返回时，up方法能保证最上方的cover[1]是修改正确的
//同时任何一次增加操作所涉及的线段树范围，后续一定能被等规模的减少操作取消掉
void update(int ql, int qr, ll qv, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        cnt[i] += qv;
        up(i, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update(ql, qr, qv, i << 1, l, mid);
    }
    if (qr > mid) {
        update(ql, qr, qv, i << 1 | 1, mid + 1, r);
    }
    up(i, l, r);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    //将纵坐标离散化
    vector<event> qx;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        qx.emplace_back(a[i].x1, 1, a[i].y1, a[i].y2);
        qx.emplace_back(a[i].x2, -1, a[i].y1, a[i].y2);
        y.emplace_back(a[i].y1);
        y.emplace_back(a[i].y2);
    }
    sort(qx.begin(), qx.end());
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    int n1 = y.size();
    //这里纵坐标y离散化之后，每个下标i管理的是y[i+1]-y[i]的长度
    //末尾加一个哨兵防止越界
    y.emplace_back(y.back());
    len.assign(n1 << 2, 0);
    cover.assign(n1 << 2, 0);
    cnt.assign(n1 << 2, 0);
    build(1, 1, n1 - 1);
    //从左到右扫描所有x
    ll sum = 0;
    ll cur = qx[0].x;
    for (int i = 0; i < 2 * n; i++) {
        //来到每个位置，先结算上一阶段的，再进行修改
        sum += 1LL * (qx[i].x - cur) * cover[1];
        cur = qx[i].x;
        auto lo = lower_bound(y.begin(), y.end(), qx[i].y1) - y.begin();
        auto hi = lower_bound(y.begin(), y.end(), qx[i].y2) - y.begin();
        update(lo, hi - 1, qx[i].d, 1, 1, n1 - 1);
    }
    cout << sum << '\n';
    return 0;
}